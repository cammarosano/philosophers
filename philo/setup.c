/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:25:54 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/20 20:26:21 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// returns array of t_philos (NULL if case of error)
static t_philo	*initialize_philos(t_params *params, t_shared *shared)
{
	t_philo	*array;
	int		i;

	array = malloc(sizeof(*array) * params->n_philos);
	if (!array)
		return (NULL);
	i = -1;
	while (++i < params->n_philos)
	{
		if (pthread_mutex_init(&array[i].meal_lock, NULL) == -1)
		{
			clear_philos(array, i);
			return (NULL);
		}
		array[i].index = i;
		array[i].meal_count = 0;
		array[i].first_fork = i;
		array[i].second_fork = (i + 1) % params->n_philos;
		array[i].shared = shared;
		array[i].params = params;
	}
	return (array);
}

static int	make_fork_locks(t_shared *mem, int n)
{
	int	i;

	mem->forks = malloc(sizeof(*(mem->forks)) * n);
	if (!mem->forks)
		return (-1);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&mem->forks[i], NULL) == -1)
		{
			destroy_locks_array(mem->forks, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

// returns 0 if successfull, -1 if error.
static int	initialize_shared_memory(t_shared *mem, int n_philos)
{
	if (pthread_mutex_init(&mem->log_lock, NULL) == -1)
		return (-1);
	if (make_fork_locks(mem, n_philos) == -1)
	{
		pthread_mutex_destroy(&mem->log_lock);
		return (-1);
	}
	mem->sim_over = 0;
	mem->start = 0;
	return (0);
}

int	setup(t_params *params, t_shared *shared, t_philo **philos)
{
	if (initialize_shared_memory(shared, params->n_philos) == -1)
		return (-1);
	*philos = initialize_philos(params, shared);
	if (!*philos)
	{
		clear_memory(NULL, shared, params->n_philos);
		return (-1);
	}
	return (0);
}
