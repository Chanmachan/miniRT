#include "../includes/libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c -= 32;
	}
	return (c);
}

/*
#include <stdio.h>

int main(void)
{
	int a = 'f';

	printf("%c", ft_toupper(a));
}
*/