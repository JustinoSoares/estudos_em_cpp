#include <iostream>
#include <map>
#include <string>

// Função que gera uma resposta HTTP

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


std::string statusText(int statusCode)
{
    std::map<int, std::string> status;

    status[200] = "OK";
    status[400] = "BAD REQUEST";
    status[404] = "NOT FOUND";
    status[401] = "UNAUTHORIZED";
    status[401] = "FORBIDDEN";
    status[500] = "INTERNAL SERVER ERROR";
    status[502] = "BAD GATEWAY";
    status[504] = "GATEWAY TIMEOUT";

    return status[statusCode] != "" ? status[statusCode] : "OK" ;
}
int	main(void)
{

    int statusCode = 200;
	const std::string response = buildResponse("Olá Justino", statusCode, statusText(statusCode));

	std::cout << "========== My resposne ============" << std::endl;
	std::cout << response << std::endl;
}