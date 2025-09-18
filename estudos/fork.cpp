#include <iostream>
#include <unistd.h>

// cria um novo processo chamado filho

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		std::cout << "Processo filho: " << getpid() << std::endl;
	else if (pid > 0)
		std::cout << "Processo pai: " << getpid() << std::endl;
	else
		std::cerr << "Erro" << std::endl;
}

// perguntar onde e como usar de forma prática