#include "../includes/libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*rtn_str;

	len = ft_strlen(str);
	rtn_str = (char *) malloc (sizeof(char) * (len + 1));
	if (rtn_str == NULL)
		return (NULL);
	i = 0;
	while (i < len && str[i] != '\0')
	{
		rtn_str[i] = str[i];
		i++;
	}
	rtn_str[i] = '\0';
	return (rtn_str);
}

//delete NULL check

/*#include <stdio.h>
#include <string.h>

int main(void)
{
	char *a = NULL;

	printf("%s\n", ft_strdup(a));
	printf("%s\n", strdup(a));
}*/
