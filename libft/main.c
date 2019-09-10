#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char* str);

int main()
{
	char	*str;

	str = "0xFFFFFF";
	printf("%d\n", (int)str);
	return (0);
}
