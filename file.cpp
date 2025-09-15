#include <fcntl.h>
#include <iostream>
#include <unistd.h>

int	main(void)
{
	char *file = "file.txt";
	int fd = open(file, O_CREAT | O_WRONLY, 0644);
	write(fd, "Olá mundo!!", 10);
	close(fd);

	fd = open(file, O_RDONLY);
	char buffer[30];

	int n = read(fd, buffer, sizeof(buffer));
	write(1, buffer, n);
	close(fd);
}