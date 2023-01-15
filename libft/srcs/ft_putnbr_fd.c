#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	long_n;

	long_n = n;
	if (long_n < 0)
	{
		ft_putchar_fd('-', fd);
		long_n *= -1;
	}
	if (long_n >= 10)
	{
		ft_putnbr_fd(long_n / 10, fd);
		ft_putnbr_fd(long_n % 10, fd);
	}
	else
		ft_putchar_fd(long_n + '0', fd);
}

/*int main(void)
{
	ft_putnbr_fd(2147483647, 1);
}*/
