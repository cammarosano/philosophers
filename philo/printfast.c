#include "philo.h"

// converts nb to a sequence of characters stored into buffer
// returns the number of characters written
int	ltoa(long nb, char *buffer)
{
	char	digits[30];
	int		n;
	int		i;

	n = 0;
	while (nb >= 10)
	{
		digits[n] = nb % 10;
		nb /= 10;
		n++;
	}
	*buffer++ = (char)nb + '0';
	i = n - 1;
	while (i >= 0)
		*buffer++ = digits[i--] + '0';
	*buffer = '\0';
	return (n + 1);
}

void	printfast(long timestamp, int philo_id, char *action, char *buffer)
{
	int	len;

	len = ltoa(timestamp, buffer);
	buffer[len++] = ' ';
	len += ltoa(philo_id, buffer + len);
	buffer[len++] = ' ';
	while (*action)
		buffer[len++] = *action++;
	buffer[len++] = '\n';
	write(1, buffer, len);
}

// int main()
// {
// 	char buffer[50];

// 	printfast(0, 50000, "has taken a fork", buffer);

// }
