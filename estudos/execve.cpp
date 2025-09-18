#include <iostream>
#include <unistd.h>

// subistituir o processo actual por um outro programa
// sintax
// int execve(const char * pathname, char *const argv[], char *const env[]);

int	main(void)
{
	char *args[] = {(char *)"/bin/ls", (char *)"-la", NULL};
	char *env[] = { NULL };

	execv("/bin/ls", args);
	perror("execve");
}

/*
/bin/ls → listar diretórios

/bin/echo → imprimir texto

/bin/cat → mostrar conteúdo de arquivo

/bin/mkdir → criar diretórios

/bin/rm → apagar arquivos

/bin/touch → criar arquivos

/usr/bin/env → mostrar variáveis de ambiente

/usr/bin/python3 → abrir interpretador Python

/usr/bin/gcc → compilador C

*/