/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:30:42 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/20 20:30:43 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (n + 1);
}

void	printfast(long timestamp, t_philo *philo, char *action)
{
	int		len;
	char	*buffer;

	buffer = philo->shared->print_buffer;
	len = ltoa(timestamp, buffer);
	buffer[len++] = ' ';
	len += ltoa(philo->index + 1, buffer + len);
	buffer[len++] = ' ';
	while (*action)
		buffer[len++] = *action++;
	buffer[len++] = '\n';
	write(1, buffer, len);
}
