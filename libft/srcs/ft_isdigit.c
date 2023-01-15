#include "../includes/libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main(void)
{
	int a = '5';
	printf("%d", ft_isdigit(a));
}
*/