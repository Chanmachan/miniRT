#include "../includes/libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\r' || \
			c == '\f' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	new_s;
	int		sign;
	size_t	i;

	new_s = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (sign == 1 && (new_s > ((LONG_MAX - sign * (str[i] - '0')) / 10)))
			return ((int)LONG_MAX);
		if (sign == -1 && (new_s < ((LONG_MIN - sign * (str[i] - '0')) / 10)))
			return ((int)LONG_MIN);
		new_s = (new_s * 10) + sign * (str[i] - '0');
		i++;
	}
	return ((int)new_s);
}

//new_s * 10 + str[i] - '0' > LONG_MAX
//new_s * 10 + sign * str[i] - '0' < LONG_MIN
//new_s < (LONG_MIN - sign * str[i] - '0') / 10

/*#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
//	char a[] = "	 \n-42 3";

//	printf("%ld\n", LONG_MIN);
	printf("%d\n", atoi("-9223372036854775809"));
	printf("%d\n", ft_atoi("-9223372036854775809"));
}*/
