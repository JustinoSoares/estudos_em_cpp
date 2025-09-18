#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

// o select serve para resposnder muitos clientes de foma simultanea

int	main(void)
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in sockAddr{};
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(8080);
	sockAddr.sin_addr.s_addr = INADDR_ANY;

	bind(server_fd, (sockaddr *)&sockAddr, sizeof(sockAddr));
	listen(server_fd, 5);

	fd_set master, readfds;
	FD_ZERO(&master);
	FD_SET(server_fd, &master);

	int fdmax = server_fd;

	std::cout << "Servidor escutando na porta 8080...\n";

	while (true)
	{
		readfds = master; // copia pos select modifica o set

		if (select(fdmax + 1, &readfds, NULL, NULL, NULL) == -1)
		{
			perror("select");
			return (1);
		}
	}

	for (int i = 0; i < fdmax; i++)
	{
		if (FD_ISSET(i, &readfds))
		{
			if (i == server_fd)
			{
				// nova conexao
				int client = accept(server_fd, NULL, NULL);
				FD_SET(client, &master);
				if (client > fdmax)
					fdmax = client;
				std::cout << "Novo cliente conectado (fd=" << client << ")\n";
			}
            else{
                // dados de um cliente
                char buf[1024];
                int bytes =  recv(i, buf, sizeof(buf), 0);
                if (bytes <= 0)
                {
                    close(i);
                    FD_CLR(i, &master);
                    std::cout << "Cliente desconectado (fd=" << i << ")\n";
                }
                else
                {
                    //Eco de volta
                    send(i, buf, bytes, 0);
                }
            }
		}
	}
}