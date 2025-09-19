#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <map>

// Estrutura Request
struct Request {
    std::string method;
    std::string path;
    std::map<std::string, std::string> headers;
    std::string body;
};

// Função auxiliar: trim espaços
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    if (start == std::string::npos || end == std::string::npos) return "";
    return str.substr(start, end - start + 1);
}

// Função principal de parsing
Request parseRequest(const std::string& raw) {
    Request req;

    std::istringstream stream(raw);
    std::string line;

    // 1. Primeira linha = Request line
    if (std::getline(stream, line)) {
        if (line.back() == '\r') line.pop_back(); // remove \r no final
        std::istringstream firstLine(line);
        firstLine >> req.method >> req.path; // ignoramos a versão agora
    }

    // 2. Headers (até linha em branco)
    while (std::getline(stream, line)) {
        if (line == "\r" || line == "" || line == "\n") break; // fim dos headers
        if (line.back() == '\r') line.pop_back(); // remove \r
        size_t pos = line.find(":");
        if (pos != std::string::npos) {
            std::string key = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 1));
            req.headers[key] = value;
        }
    }

    // 3. Body (restante do stream)
    std::string body;
    while (std::getline(stream, line)) {
        if (line.back() == '\r') line.pop_back();
        body += line + "\n";
    }
    req.body = body;

    return req;
}

// testando 
int main() {
    std::string rawRequest =
        "POST /login HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: curl/7.68.0\r\n"
        "Content-Length: 13\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "\r\n"
        "username=joe\n";

    Request req = parseRequest(rawRequest);

    std::cout << "Method: " << req.method << std::endl;
    std::cout << "Path: " << req.path << std::endl;

    std::cout << "Headers:" << std::endl;
    for (auto &h : req.headers) {
        std::cout << "  " << h.first << ": " << h.second << std::endl;
    }

    std::cout << "Body: " << req.body << std::endl;

    return 0;
}

