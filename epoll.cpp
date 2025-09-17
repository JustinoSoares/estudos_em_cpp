#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

int	main(void)
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(server_fd, (sockaddr *)&addr, sizeof(addr));
	listen(server_fd, 10);

	int epfd = epoll_create1(0);

	epoll_event ev{}, events[10];
	ev.events = EPOLLIN;
	ev.data.fd = server_fd;
	epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &ev);

	while (true)
	{
		int nfds = epoll_wait(epfd, events, 10, -1);
		for (int i = 0; i < nfds; i++)
		{
			if (events[i].data.fd == server_fd)
			{
				// nova conexão
                std::cout << "Nova conexao com o id: " + i << std::endl;
				int client_fd = accept(server_fd, nullptr, nullptr);
				ev.events = EPOLLIN;
				ev.data.fd = client_fd;
				epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);
			}
			else
			{
				// dados de um cliente
				char buf[1024];
				int n = read(events[i].data.fd, buf, sizeof(buf));
				if (n <= 0)
				{
					close(events[i].data.fd);
					epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, nullptr);
				}
				else
				{
					std::cout << "Recebi: " << std::string(buf, n) << "\n";
				}
			}
		}
	}
}