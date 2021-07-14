#include "philo.h"

static void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->index % 2)
		usleep(1000); // give a head start to even index philos
	
	while (!philo->shared->sim_over)
	{
		ph_get_first_fork(philo);
		if (philo->params->n_philos < 2) // release fork and wait to be declared dead
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

int	main(int argc, char **argv)
{
	t_params		params;
	t_shared_mem	shared;
	t_philo 		*philos;
	int				i;

	if (parse_params(argc, argv, &params) == -1)
		return (1);
	if (setup(&params, &shared, &philos) == -1)
		return (1);
	i = -1;	
	while (++i < params.n_philos)
		pthread_create(&philos[i].thread_id, NULL, philosopher, &philos[i]);
	while (!shared.sim_over)
	{
		check_4_deaths(philos, &params, &shared);
		if (params.meals_2_eat)
			check_n_meals(philos, &params, &shared);
	}
	i = -1;
	while (++i < params.n_philos)
		pthread_join(philos[i].thread_id, NULL);
	clear_memory(philos, &shared, params.n_philos);
	return (0);
}
