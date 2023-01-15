#include "../includes/libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main(void)
{
	int a = ' ';
	printf("%d", ft_isalnum(a));
}
*/