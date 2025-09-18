#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

// espera um processo filho terminar
int	main(void)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		std::cout << "Executando o processo filho" << std::endl;
		execlp("sleep", "sleep", "2", NULL);
	}
	else
	{
		int status;

		std::cout << "Antes do processo filho terminar" << std::endl;
		waitpid(pid, &status, 0);
		std::cout << "Processo filho terminou" << status << std::endl;
	}
}