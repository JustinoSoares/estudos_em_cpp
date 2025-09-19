#include <stdio.h>

int	main(void)
{
	int count;
	int total = 0;
	int _tc = 0;
	int _tr = 0;
	int _ts = 0;

	scanf("%d\n", &count);

	for (int i = 0; i < count; i++)
	{
		int value;
		char c;

		value = 0;
		scanf("%d %c", &value, &c);

		total += value;
		if (c == 'C')
			_tc += value;
		else if (c == 'R')
			_tr += value;
		if (c == 'S')
			_ts += value;
		else
			continue ;
	}

	printf("Total: %d cobaias\n", total);
	printf("Total de coelhos: %d\n", _tc);
	printf("Total de ratos: %d\n", _tr);
	printf("Total de sapos: %d\n", _ts);

	printf("Percentual de coelhos: %.2f %%\n", ((float)100 * _tc) / total);
	printf("Percentual de ratos: %.2f %%\n", ((float)100 * _tr) / total);
	printf("Percentual de sapos: %.2f %%\n", ((float)100 * _ts) / total);

	return (0);
}