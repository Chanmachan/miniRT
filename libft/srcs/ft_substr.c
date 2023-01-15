#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rtn_str;
	size_t	len_s;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < start)
		return (ft_strdup(""));
	if (len > len_s - start)
		len = len_s - start;
	rtn_str = (char *) malloc (sizeof(char) * (len + 1));
	if (rtn_str == NULL)
		return (NULL);
	ft_strlcpy(rtn_str, &s[start], len + 1);
	return (rtn_str);
}

//L16 new_s[start] != '\0' important
//return (null) if s == NULL to avoid SIGSEGV

/*#include <stdio.h>

int main(void)
{
	char a[] = "\0";
	unsigned int b = 8;
	size_t c = 14;

	printf("%s\n", ft_substr(a, b, c));
}*/
