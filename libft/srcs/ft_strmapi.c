#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*rtn_str;
	size_t			len_s;
	size_t			i;

	if (s == NULL || f == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	rtn_str = (char *)malloc(sizeof(char) * (len_s + 1));
	if (rtn_str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		rtn_str[i] = f(i, s[i]);
		i++;
	}
	rtn_str[i] = '\0';
	return (rtn_str);
}

/*
#include <stdio.h>

char	additional_func(unsigned int i, char c)
{
	return (i + c);
}

int main(void)
{
	char	*str = ft_strmapi("1234", additional_func);

	printf("%s\n", str);
}
 */