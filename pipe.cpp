//#include <fcntl.h>
#include <iostream>
#include <unistd.h>

// cria cominicação entre processos
int	main(void)
{
	int		fds[2];
    
	pipe(fds);
	if (fork() == 0)
	{
        close(fds[1]);
        char	bf[30];
		read(fds[0], bf, sizeof(bf));
		std::cout << "Filho recebeu: " << bf << std::endl;
	}
	else
	{
		close(fds[0]);
		write(fds[1], "Maluco\n", 8);
	}
}

/*
| Posição  | Descritor   | Usado para                         |
| -------- | ----------- | ---------------------------------- |
| `fds[0]` | **leitura** | você lê dados que chegaram no pipe |
| `fds[1]` | **escrita** | você escreve dados para o pipe     |
*/