#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *) s)[i] == (unsigned char) c)
		{
			return ((unsigned char *) s + i);
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	unsigned char s[] = "abcdefg";
	int c = 'c';

	printf("%s\n", (char *)memchr(s, c, 8));
	printf("%s\n", (char *)ft_memchr(s, c, 8));
}
*/