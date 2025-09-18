#include <cstring> // memset()
#include <iostream>
#include <netinet/in.h> // sockaddr_in
#include <sys/socket.h> // socket(), bind(), listen(), accept()
#include <unistd.h>     // read(), write(), close()

/*
🧩 Dividindo o Webserver em Mini Projetos
🔹 Parte 1 — Redes e Conexões (Sockets)

🎯 Objetivo: criar um servidor TCP que aceite conexões.

Criar socket com socket().

Fazer bind numa porta (ex: 8080).

Fazer listen para aceitar clientes.

Usar	accept(void) para pegar a conexão.

Escrever e ler do cliente.

👉 Mini projeto:
Servidor que, ao conectar, manda a mensagem "Hello client!" e fecha.
*/

int	main(void)
{
	int			server_fd;
	sockaddr_in	address;
	socklen_t	addrlen;
	int			client_fd;
	const char	*msg = "Hello client!\n";

	// 1. Criar socket (IPv4, TCP)
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		perror("socket");
		return (1);
	}
	// 2. Configurar endereço (porta 8080)
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;         // IPv4
	address.sin_addr.s_addr = INADDR_ANY; // aceitar conexões de qualquer IP
	address.sin_port = htons(8080);       // porta 8080
	// 3. Fazer bind (ligar socket à porta)
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind");
		close(server_fd);
		return (1);
	}
	// 4. Colocar em modo listen (esperando conexões)
	if (listen(server_fd, 5) < 0)
	{
		perror("listen");
		close(server_fd);
		return (1);
	}
	std::cout << "Servidor rodando na porta 8080, \
		esperando conexões..." << std::endl;
	// 5. Aceitar conexão de um cliente
	addrlen = sizeof(address);
	client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
	if (client_fd < 0)
	{
		perror("accept");
		close(server_fd);
		return (1);
	}
	std::cout << "Cliente conectado!" << std::endl;
	// 6. Enviar mensagem para o cliente
	write(client_fd, msg, strlen(msg));
	// 7. Fechar conexões
	close(client_fd);
	close(server_fd);
	return (0);
}
