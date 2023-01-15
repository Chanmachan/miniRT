#include "../includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	uc;
	size_t			i;

	uc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = uc;
		i++;
	}
	return (s);
}

// L10 brackets are important