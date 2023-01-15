#include "../includes/libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c += 32;
	}
	return (c);
}

/*
#include <stdio.h>

int main(void)
{
	int a = '8';

	printf("%c", ft_tolower(a));
}
*/