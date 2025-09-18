#include <fcntl.h>
#include <iostream>
#include <unistd.h>

// duplicar um file descriptor
int	main(void)
{
	int fd = open("saida.txt", O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
	{
		std::cerr << "Erro" << std::endl;
		return (1);
	}
	dup2(fd, 1); // stdout -> arquivo
	write(1, "Vai para o arquivo\n", 30);
	close(fd);
}