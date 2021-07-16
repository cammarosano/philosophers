#include "philo.h"

void	switch_forks(t_philo *philo)
{
	int	temp;

	temp = philo->first_fork;
	philo->first_fork = philo->second_fork;
	philo->second_fork = temp;
}

// returns array of t_philos (NULL if case of error)
// Deadlock is prevented by philos of odd number grabing first the fork at
// his right, as opposed to even numbered philos (left fork first)
static t_philo *initialize_philos(t_params *params, t_shared_mem *shared)
{
	t_philo	*array;
	int		i;

	array = malloc(sizeof(*array) * params->n_philos);
	if (!array)
		return (NULL);
	i = -1;
	while (++i < params->n_philos)
	{
		array[i].index = i;
		// array[i].last_meal = shared->start_time;
		array[i].meal_count = 0;
		if (pthread_mutex_init(&array[i].meal_lock, NULL) == -1)
			return (NULL); // TODO error handling (remember to clear memory at program exit, when success)
		array[i].shared = shared;
		array[i].params = params;
		array[i].first_fork = i;
		array[i].second_fork = (i + 1) % params->n_philos;
		// if (i % 2)
			// switch_forks(&array[i]);
	}
	// switch_forks(&array[params->n_philos - 1]);

	return (array);
}

static int	make_fork_locks(t_shared_mem *mem, int n)
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
static int	initialize_shared_memory(t_shared_mem *mem, int n_philos)
{
	if (pthread_mutex_init(&mem->log_lock, NULL) == -1)
		return (-1);
	if (make_fork_locks(mem, n_philos) == -1)
	{
		pthread_mutex_destroy(&mem->log_lock);
		return (-1);
	}
	// if (gettimeofday(&mem->start_time, NULL) == -1)
	// {
	// 	destroy_locks_array(mem->forks, n_philos);
	// 	pthread_mutex_destroy(&mem->log_lock);
	// 	return (-1);
	// }
	mem->sim_over = 0;
	mem->start = 0;
	return (0);
}

int	setup(t_params *params, t_shared_mem *shared, t_philo **philos)
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
