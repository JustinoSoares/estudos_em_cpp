#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// a Função socket criar um endpoint de comunicação(um descritot de arquivo especial
// como se fosse um fd de pipe para redes)

// int socket(int domain, int type, int protocol);
/*
	domain -> Especifica a familia de protocolo
		* AF_INET -> IPV4
		* AF_INET6 -> IPV6
		* AF_UNIX -> comunicação local entre processos do mesmo sistema
	type -> tipo de socket
		* SOCK_STREAM -> socket origientado a conexao (TCP)
		* SOCK_DGRAM -> datagramas (UDP)
		* SOCK_RAM -> acesso a protocolos de baixo nível
	protocol -> geralmente é 0, o sistema escolhe automáticamente o protocolo
		Exemplo: para SOCK_STREAM + AF_INET, o protocolo padrão é o TCP.
	- Retorno
	Descritor do socket (fd).
	-1 em caso de erro.
*/

/*
	int bind(int sockfd, const struct sockaddr * addr, socklen_t addrlen);

	* sockfd → socket criado por socket().
	* addr → estrutura com IP e porta (struct sockaddr_in para IPv4).
	* addrlen → tamanho da estrutura.
*/
int	main(void)
{
	// criar o socket
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind(server_fd, (sockaddr *)&addr, sizeof(addr));

	listen(server_fd, 5);

	std::cout << "Server listing..." << std::endl;
	while (true)
	{
		int client = accept(server_fd, NULL, NULL);
		const char *msg = "Ola cliente\n";
		send(client, msg, strlen(msg) + 5, 0);
		close(client);
	}

	close(server_fd);
}