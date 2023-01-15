#include "../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*rtn_str;
	size_t	start;
	size_t	end;
	size_t	len;
	size_t	size;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup((char *)s1));
	len = ft_strlen(s1);
	start = 0;
	end = len;
	while (start < len && ft_strchr(set, s1[start]))
		start++;
	while (start < end && ft_strchr(set, s1[end - 1]))
		end--;
	if (start == end)
		return (ft_strdup(""));
	size = end - start;
	rtn_str = ft_substr((char *)s1 + start, 0, size);
	return (rtn_str);
}

//if set is NULL -> return (s1)

/*#include <stdio.h>

int main(void)
{
	char *a = ft_strtrim("   xxx   xxx", " x");
	printf("%s\n", a);
	free(a);
}*/
