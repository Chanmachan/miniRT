#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == src || n == 0)
		return (dst);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
//still copy if '\0'
//if both args == NULL return (NULL)

/*#include <stdio.h>
#include <string.h>

int main()
{
	char *dest = NULL;
	char *src = "abc";
	ft_memcpy(dest, src, 4);
	printf("%s\n", dest);
	char *dest2 = "abc";
	char *src2 = NULL;
	memcpy(dest2, src2, 4);
	printf("%s\n", dest2);
}*/
