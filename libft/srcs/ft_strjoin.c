#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rtn_str;
	size_t	len_rtn_str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_rtn_str = ft_strlen(s1) + ft_strlen(s2);
	rtn_str = (char *) malloc (sizeof(char) * (len_rtn_str + 1));
	if (rtn_str == NULL)
		return (NULL);
	ft_strlcpy(rtn_str, s1, ft_strlen(s1) + 1);
	ft_strlcat(rtn_str, s2, len_rtn_str + 1);
	return (rtn_str);
}

/*#include <string.h>
#include <stdio.h>

int main(void)
{
	char *a = "abcd";
	char *b = NULL;

	printf("%s\n", ft_strjoin(a, b));
}*/
