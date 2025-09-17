#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

int	main(void)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in sockAddr{};
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(8080);

	inet_pton(AF_INET, "127.0.0.1", &sockAddr.sin_addr);

	// conectar n o servidor
	if (connect(sock, (sockaddr *)&sockAddr, sizeof(sockAddr)) < 0)
	{
		perror("connect");
		std::cout << "Não foi possível manter a connexão com servidor\n" << std::endl;
		return (1);
	}

	std::cout << "Connectando ao servidor\n";

	char buf[1024];
	int bytes = recv(sock, buf, sizeof(buf) - 1, 0);

	if (bytes > 0)
	{
		std::cout << "Message receive: " << buf << std::endl;
	}
	else if (bytes == 0)
	{
		std::cout << "O Servidor fechou a conexão";
	}
	else
	{
		std::cout << "Erro ao reber a mensagem" << std::endl;
	}
	close(sock);
	return (0);
}