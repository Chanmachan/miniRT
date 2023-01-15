#include "../includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s2[j] == '\0')
		return ((char *) s1);
	if (len == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		j = 0;
		while ((s1[i + j] == s2[j] || s2[j] == '\0') && (i + j) <= len)
		{
			if (s2[j] == '\0')
				return (((char *) s1) + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*#include <string.h>
#include <stdio.h>

int main(void)
{
	char *a = NULL;
	char b[] = "\0";
	size_t	len = 9;

	printf("%s\n", ft_strnstr(a, b, len));
	printf("%s\n", strnstr(a, b, len));
}*/
