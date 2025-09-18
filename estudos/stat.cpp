#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

int	main(void)
{
	struct stat info{};

	if (stat("saida.txt", &info) == 0)
		std::cout << info.st_size << std::endl;
}