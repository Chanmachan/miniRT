#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*new_s;
	size_t	i;

	new_s = (char *) s;
	i = 0;
	while (new_s[i] != '\0')
	{
		if (new_s[i] == (char) c)
			return (new_s + i);
		i++;
	}
	if ((char) c == '\0')
		return (new_s + i);
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char a[] = "abcdefg";
	int b = '\0';

	printf("%s\n", ft_strchr(a, b));

	char c[] = "abcdefg";
	int d = '\0';

	printf("%s\n", strchr(c, d));
}
*/