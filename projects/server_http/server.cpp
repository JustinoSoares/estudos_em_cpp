#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() {
    // 1. Criar socket (IPv4, TCP)
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    // Permitir reuso rápido da porta (evita "Address already in use")
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 2. Configurar endereço (porta 8080)
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    std::cout << "Servidor HTTP rodando na porta 8080..." << std::endl;

    // Loop para atender clientes (um por vez)
    while (true) {
        socklen_t addrlen = sizeof(address);
        int client_fd = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        std::cout << "\n📩 Cliente conectado!" << std::endl;

        // 3. Ler request do cliente
        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

        if (bytes_read > 0) {
            std::cout << "=== HTTP Request Recebida ===" << std::endl;
            std::cout << buffer << std::endl;
            std::cout << "=============================" << std::endl;
        }

        // 4. Criar resposta HTTP/1.1
        const char* body = "Hello World!\n";
        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: " + std::to_string(strlen(body)) + "\r\n"
            "Connection: close\r\n"
            "\r\n" +
            std::string(body);

        // 5. Enviar resposta
        write(client_fd, response.c_str(), response.size());

        // 6. Fechar conexão
        close(client_fd);
    }

    close(server_fd);
    return 0;
}
