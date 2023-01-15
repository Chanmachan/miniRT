#include "../includes/libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*rtn_box;

	if (n == 0 || size == 0)
		return (ft_calloc(1, 1));
	if (n > SIZE_MAX / size)
		return (NULL);
	rtn_box = (void *) malloc(n * size);
	if (rtn_box == NULL)
		return (NULL);
	ft_memset(rtn_box, 0, n * size);
	return (rtn_box);
}

/*#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *str;

	str = ft_calloc(0, 0);
	ft_memset(str, 3, ft_strlen(str));
	printf("%s\n", str);
}*/

/*
void	*ft_calloc(size_t n, size_t size)
{
	void	*rtn_box;
	if(n <= 4294967295 && size <= 42949667295)
	{
		rtn_box = (void *) malloc (n * size);
		if (rtn_box == NULL)
			return (NULL);
		ft_memset(rtn_box, 0, n * size);
		return (rtn_box);
	}
	return (NULL);
}*/
//proto
