/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:31:17 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/20 20:31:18 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_locks_array(pthread_mutex_t *array, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&array[i]);
		i++;
	}
	free(array);
}

void	clear_philos(t_philo *philos, int n)
{
	int	i;

	if (!philos)
		return ;
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&philos[i].meal_lock);
		i++;
	}
	free(philos);
}

void	clear_memory(t_philo *philos, t_shared *shared, int n_philos)
{
	destroy_locks_array(shared->forks, n_philos);
	pthread_mutex_destroy(&shared->log_lock);
	clear_philos(philos, n_philos);
}
