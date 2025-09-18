#include <iostream>
#include <signal.h>
#include <unistd.h>

void	handle(int sig)
{
	std::cout << " O sinal " << sig << std::endl;
	exit(0);
}

int	main(void)
{
	signal(SIGUSR1, handle); // signal definido pelo usuário

    // chamar o sinal
    //kill(pid, sig);
	std::cout << getpid() << std::endl;
	while (1)
		pause();
}

/*

| Sinal     | Nº | Significado                                 | Padrão de ação                     |
| --------- | -- | ------------------------------------------- | ---------------------------------- |
| `SIGHUP`  | 1  | Hangup (terminal fechado,
	perda de conexão) | Termina o processo                 |
| `SIGINT`  | 2  | Interrupção (Ctrl+C)                        | Termina o processo                 |
| `SIGQUIT` | 3  | Quit (Ctrl+\\)                              | Termina
	+ gera core dump           |
| `SIGILL`  | 4  | Instrução ilegal                            | Core dump                          |
| `SIGABRT` | 6  | Abort (`abort()`)                           | Core dump                          |
| `SIGFPE`  | 8  | Erro aritmético (ex.: divisão por zero)     | Core dump                          |
| `SIGKILL` | 9  | Mata o processo (não pode ser capturado)    | Termina imediatamente              |
| `SIGSEGV` | 11 | Violação de memória (segmentation fault)    | Core dump                          |
| `SIGPIPE` | 13 | Escrita em pipe sem leitor                  | Termina o processo                 |
| `SIGALRM` | 14 | Timer (`alarm()`) expirou                   | Termina o processo                 |
| `SIGTERM` | 15 | Pedido de término (graceful shutdown)       | Termina o processo                 |
| `SIGUSR1` | 10 | Sinal definido pelo usuário (customizado)   | Termina o processo (se não tratar) |
| `SIGUSR2` | 12 | Outro sinal customizado                     | Termina o processo                 |
| `SIGCHLD` | 17 | Processo filho terminou ou parou            | Ignorado por padrão                |
| `SIGCONT` | 18 | Continua processo parado                    | Continua execução                  |
| `SIGSTOP` | 19 | Para execução (não pode ser capturado)      | Suspende o processo                |
| `SIGTSTP` | 20 | Parar do terminal (Ctrl+Z)                  | Suspende o processo                |

*/