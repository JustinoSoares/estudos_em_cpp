#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

// Função para detectar Content-Type básico
std::string getContentType(const std::string& path) {
    if (path.find(".html") != std::string::npos) return "text/html";
    if (path.find(".txt")  != std::string::npos) return "text/plain";
    if (path.find(".css")  != std::string::npos) return "text/css";
    if (path.find(".js")   != std::string::npos) return "application/javascript";
    return "application/octet-stream"; // genérico
}

// Função para ler arquivo inteiro para string
std::string readFile(const std::string& filename) {
    std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
    if (!file) {
        return "";
    }
    std::ostringstream contents;
    contents << file.rdbuf();
    file.close();
    return contents.str();
}

std::string statusText(int statusCode)
{
    std::map<int, std::string> status;

    status[200] = "OK";
    status[400] = "BAD REQUEST";
    status[404] = "NOT FOUND";
    status[401] = "UNAUTHORIZED";
    status[401] = "FORBIDDEN";
    status[405] = "METHOD NOT ALLOWED";
    status[500] = "INTERNAL SERVER ERROR";
    status[502] = "BAD GATEWAY";
    status[504] = "GATEWAY TIMEOUT";

    return status[statusCode] != "" ? status[statusCode] : "OK" ;
}

// Função para montar response HTTP
std::string buildResponse(const std::string &body, int statusCode = 200,
    const std::string statusText = "OK",
	const std::string &contentType = "text/plain"
	)
{
	// status line
	std::string response = "HTTP/1.1 " + std::to_string(statusCode) + " "
		+ statusText + "\r\n";
	// HEADER
	response += "Content-Type: " + contentType + "\r\n";
	response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
	response += "Connection: close\r\n";
	response += "\r\n"; // Linha em branco obrigatória
	// Body
	response += body;
	return (response);
}



// Estrutura Request simplificada
struct Request {
    std::string method;
    std::string path;
};

// Parser muito simples só para teste
Request parseRequest(const std::string& raw) {
    Request req;
    std::istringstream stream(raw);
    stream >> req.method >> req.path; // só pega primeira linha
    return req;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    std::cout << "Servidor rodando na porta 8080..." << std::endl;

    while (true) {
        socklen_t addrlen = sizeof(address);
        int client_fd = accept(server_fd, (struct sockaddr*)&address, &addrlen);

        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));
        read(client_fd, buffer, sizeof(buffer) - 1);

        Request req = parseRequest(buffer);
        std::string response;

        if (req.method == "GET") {
            // Remove "/" inicial do path
            std::string filename = req.path == "/" ? "index.html" : req.path.substr(1);

            std::string body = readFile(filename);
            if (!body.empty()) {
                response = buildResponse(body, 200, statusText(200), getContentType(filename));
            } else {
                response = buildResponse("<h1>404 Not Found</h1>", 404, statusText(404), "text/html");
            }
        } else {
            response = buildResponse("<h1>405 Method Not Allowed</h1>", 405, statusText(405), "text/html");
        }

        write(client_fd, response.c_str(), response.size());
        close(client_fd);
    }

    close(server_fd);
    return 0;
}


