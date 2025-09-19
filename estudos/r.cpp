#include <chrono>
#include <iostream>
#include <thread>

int	main(void)
{
	// Exemplo 1: sobrescrevendo na mesma linha
	std::cout << "Carregando..."
				<< "\r";
	std::cout << "Concluído!" << std::endl;

	// Exemplo 2: animação simples com \r
	for (int i = 0; i <= 100; i += 20)
	{
		std::cout << "\rProgresso: " << i << "%";
		std::cout.flush(); // força imprimir imediatamente
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	std::cout << std::endl;
}