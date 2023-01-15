#include "../includes/libft.h"

static size_t	count_array(char const *str, char c)
{
	size_t	i;
	size_t	num_array;

	i = 0;
	num_array = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != c && str[i] != '\0')
		{
			while (str[i] != c && str[i] != '\0')
				i++;
			num_array++;
		}
	}
	return (num_array);
}

char	*advance_str(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	s = s + i;
	return (s);
}

static char	**allfree(char **rtn_str)
{
	size_t	i;

	i = 0;
	while (rtn_str[i] != NULL)
	{
		free(rtn_str[i]);
		i++;
	}
	free(rtn_str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**rtn_str;
	size_t	i;
	size_t	j;
	size_t	array;

	if (s == NULL)
		return (NULL);
	array = count_array(s, c);
	rtn_str = (char **) malloc (sizeof(char *) * (array + 1));
	if (rtn_str == NULL)
		return (NULL);
	j = 0;
	while (j < array)
	{
		i = 0;
		s = advance_str((char *)s, c);
		while (((char *)s)[i] != '\0' && ((char *)s)[i] != c)
			i++;
		rtn_str[j] = ft_substr(s, 0, i);
		if (rtn_str[j++] == NULL)
			return (allfree(rtn_str));
		s = s + i;
	}
	rtn_str[j] = NULL;
	return (rtn_str);
}

//if_null_func -> return string only

/*#include <stdio.h>

int main(void)
{
	char	a[] = "hello,world,42,tokyo";
	char	b = ',';

	char	**c = ft_split(a, b);
	printf("%s\n", c[0]);
	printf("%s\n", c[1]);
	printf("%s\n", c[2]);
	printf("%s\n", c[3]);
}*/

/*#include <stdio.h>

int	main(void)
{
	char	src[] = "      ";
	char	c = ' ';
	char	**sep_str;
	char	**tmp_sep_str;
	char	**tmp2_sep_str;

	if (!(sep_str = ft_split(src, c)))
		return (0);
	tmp_sep_str = sep_str;
	tmp2_sep_str = sep_str;
	while (*sep_str)
		printf("%s\n", *sep_str++);
	while (*tmp_sep_str)
		free(*tmp_sep_str++);
	free(*tmp_sep_str);
	free(tmp2_sep_str);
	return (0);
}*/