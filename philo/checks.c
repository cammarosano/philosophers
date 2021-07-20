/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:36:14 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/20 20:36:15 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_4_deaths(t_philo *philos, t_params *params, t_shared *shared)
{
	struct timeval	current_time;
	long			timestamp;
	int				i;

	i = -1;
	while (++i < params->n_philos && !shared->sim_over)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		gettimeofday(&current_time, NULL);
		if (time_diff(philos[i].last_meal, current_time) >= params->time_to_die)
		{
			pthread_mutex_lock(&shared->log_lock);
			timestamp = time_diff(shared->start_time, current_time);
			printf("%ld %d is dead\n", timestamp, i + 1);
			shared->sim_over = 1;
			pthread_mutex_unlock(&shared->log_lock);
		}
		pthread_mutex_unlock(&philos[i].meal_lock);
	}
}

void	check_n_meals(t_philo *philos, t_params *params, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < params->n_philos)
	{
		if (philos[i].meal_count < params->meals_2_eat)
			return ;
		i++;
	}
	pthread_mutex_lock(&shared->log_lock);
	shared->sim_over = 1;
	pthread_mutex_unlock(&shared->log_lock);
}

/* Notes: 
shared.sim_over is protected by the shared.log_lock

philo.last_meal is protected by the philo.meal_lock.  Even though only philo
writes to it, it protects against a philo starting to eat and dying at the
same time

philo.meal_count is not protected by lock, even though check_n_meals reads it.
*/
