#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*new_s1;
	unsigned char	*new_s2;
	size_t			i;

	new_s1 = (unsigned char *) s1;
	new_s2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (new_s1[i] != new_s2[i])
		{
			return (new_s1[i] - new_s2[i]);
		}
		i++;
	}
	return (0);
}

/*
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	unsigned char a[] = " \0";
	unsigned char b[] = " \0";
	int	c = 5;
	size_t	i;

	i = 0;
	while (i == 5)
	{
			write(1, &a[i], 1);
			i++;
	}
	printf("%2d\n", memcmp(a, b, c));
	printf("%2d\n", ft_memcmp(a, b, c));
}
*/

/*
#include <stdio.h>
#include <string.h>

int main()
{
        printf("%d\n", ft_memcmp("abc\0def", "abc\0def", 7));
        printf("%d\n", ft_memcmp("abc\0def", "aBc\0def", 7));
        printf("%d\n", ft_memcmp("abc\0def", "abc\0Def", 7));
}
*/