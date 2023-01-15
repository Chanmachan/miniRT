#include "../includes/libft.h"

static size_t	get_digit(long long num)
{
	size_t	digit;

	digit = 1;
	if (num < 0)
	{
		num *= -1;
		digit++;
	}
	while (num >= 10)
	{
		num = num / 10;
		digit++;
	}
	return (digit);
}

static long	if_int_minus(long long num, char *chr_n, size_t *sign)
{
	chr_n[0] = '-';
	num = num * -1;
	*sign = 1;
	return (num);
}

static char	*put_char_num(long long num, char *chr_n, size_t len, size_t sign)
{
	while (len > 0)
	{
		chr_n[len] = num % 10 + '0';
		num = num / 10;
		len--;
	}
	if (sign == 0)
		chr_n[0] = num % 10 + '0';
	return (chr_n);
}

char	*ft_itoa(int n)
{
	char		*chr_n;
	size_t		len_n;
	size_t		sign;
	long long	long_n;

	long_n = n;
	sign = 0;
	len_n = get_digit(long_n);
	chr_n = (char *)malloc(sizeof(char) * (len_n + 1));
	if (chr_n == NULL)
		return (NULL);
	if (n < 0)
		long_n = if_int_minus(n, chr_n, &sign);
	chr_n[len_n] = '\0';
	chr_n = put_char_num(long_n, chr_n, len_n - 1, sign);
	return (chr_n);
}

/*#include <stdio.h>

int main(void)
{
	printf("%s\n", ft_itoa(423789));
}*/

//int -> -2147483648 <= n <= 2147483647

/*//before upper itoa
#include "libft.h"
#include <stdio.h>

char	*ft_itoa(int n)
{
	char	*chr_n;
	size_t 	len_n;
	int 	tmp_n;
	size_t 	chanma;

	tmp_n = n;
	len_n = 2;
	chanma = 0;
	if (tmp_n == -2147483648)
	{
		len_n = 11;
	}
	if (tmp_n < 0)
	{
		len_n++;
		tmp_n = tmp_n * -1;
	}
	while (tmp_n >= 10)
	{
		printf("--------------------------\nlen_n\t: %zu\n", len_n);
		tmp_n = tmp_n / 10;
		len_n++;
	}
	printf("len_n = %zu\n", len_n);
	chr_n = (char *)malloc(sizeof(char) * (len_n + 1));
	if (n == -2147483648)
	{
		chr_n[0] = '-';
		chr_n[1] = '2';
		n = 147483648;
		chanma = 2;
	}
	if (n < 0)
	{
		chr_n[0] = '-';
		n = n * -1;
		printf("change_minus -> n = %d\n", n);
		chanma = 1;
	}
	chr_n[len_n] = '\0';
	len_n = len_n - 1;
	while (len_n-- > chanma)
	{
		chr_n[len_n] = n % 10 + 48;
		n = n / 10;
		printf("chr_n[%zu]\t: %c\n-------------------------\n", len_n, chr_n[len_n]);
	}
	return (chr_n);
}
*/