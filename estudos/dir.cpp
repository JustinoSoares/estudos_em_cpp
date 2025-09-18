//#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <dirent.h>

// ler os arquivos e diretorio de uma pasta
int main(void)
{
    DIR *dir = opendir(".");
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL)
        std::cout << entry->d_off  << " : "<< entry->d_name << std::endl;
    closedir(dir);
}