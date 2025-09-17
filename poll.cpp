#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <poll.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    std::vector<pollfd> fds;
    fds.push_back({server_fd, POLLIN, 0});

    std::cout << "Servidor rodando na porta 8080...\n";

    while (true) {
        int ret = poll(fds.data(), fds.size(), -1); // espera infinito
        if (ret < 0) {
            perror("poll");
            break;
        }

        for (size_t i = 0; i < fds.size(); i++) {
            if (fds[i].revents & POLLIN) {
                if (fds[i].fd == server_fd) {
                    // Nova conexão
                    int client = accept(server_fd, NULL, NULL);
                    fds.push_back({client, POLLIN, 0});
                    std::cout << "Novo cliente conectado (fd=" << client << ")\n";
                } else {
                    // Dados de um cliente existente
                    char buf[1024];
                    int bytes = recv(fds[i].fd, buf, sizeof(buf), 0);

                    if (bytes <= 0) {
                        std::cout << "Cliente desconectado (fd=" << fds[i].fd << ")\n";
                        close(fds[i].fd);
                        fds.erase(fds.begin() + i);
                        i--; // ajustar índice
                    } else {
                        send(fds[i].fd, buf, bytes, 0); // ecoa de volta
                    }
                }
            }
        }
    }

    close(server_fd);
    return 0;
}
