#include "philo.h"

// waits for the start signal
// odd index philos wait and give a head start to even philos
// in case of one philo only simulation, after getting first fork, releases it
// returns (shall be declared dead by the main thread)
static void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = arg;

	while (!philo->shared->start)
		usleep(50);
	if (philo->index % 2)
		usleep(philo->params->time_to_eat * 500);
	
	while (!philo->shared->sim_over)
	{
		ph_get_first_fork(philo);
		if (philo->params->n_philos < 2)
		{
			pthread_mutex_unlock(&philo->shared->forks[philo->first_fork]);
			return (NULL);
		}
		ph_get_2nd_fork_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}

void	end_simulation(t_philo *philos, t_shared_mem *shared, int n_philos)
{
	int	i;

	i = -1;
	while (++i < n_philos)
		pthread_join(philos[i].thread_id, NULL);
	clear_memory(philos, shared, n_philos);
}

// signal threads to start but not enter the loop, then join threads.
static void	end_simulation_error(t_philo *philos, t_shared_mem *shared, int n_threads)
{
	int	i;

	shared->sim_over = 1;
	shared->start = 1;

	i = 0;
	while (i < n_threads)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}

// create threads, initialize clocks and signal threads to start simulation
int	start_simulation(t_philo *philos, t_shared_mem *shared, int n_philos)
{
	int	i;

	i = -1;	
	while (++i < n_philos)
	{
		if (pthread_create(&philos[i].thread_id, NULL, philosopher, &philos[i]) != 0)
		{
			end_simulation_error(philos, shared, i);
			clear_memory(philos, shared, n_philos);
			return (-1);
		}
	}
	gettimeofday(&shared->start_time, NULL);
	i = -1;
	while (++i < n_philos)
		philos[i].last_meal = shared->start_time;
	shared->start = 1;
	return (0);
}


int	main(int argc, char **argv)
{
	t_params		params;
	t_shared_mem	shared;
	t_philo 		*philos;

	if (parse_params(argc, argv, &params) == -1)
		return (1);
	if (setup(&params, &shared, &philos) == -1)
		return (1);
	if (start_simulation(philos, &shared, params.n_philos) == -1)
		return (1);	
	// check for deaths or satisfaction
	while (!shared.sim_over)
	{
		check_4_deaths(philos, &params, &shared);
		if (params.meals_2_eat)
			check_n_meals(philos, &params, &shared);
	}
	// clean up and leave
	end_simulation(philos, &shared, params.n_philos);
	return (0);
}
