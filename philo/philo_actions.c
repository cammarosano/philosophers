#include "philo.h"

// general principles: for every action (take a fork, eat, sleep, think),
// once the philo has got the LOG lock, he checks whether he's not dead and
// if the simulation is not over (due to someone else's death)

void	ph_get_first_fork(t_philo *philo)
{
	struct timeval	current_time;
	long			timestamp;

	pthread_mutex_lock(&philo->shared->forks[philo->first_fork]);
	pthread_mutex_lock(&philo->shared->log_lock);
	if (philo->shared->sim_over || is_dead(philo, &current_time))
	{
		pthread_mutex_unlock(&philo->shared->log_lock);
		pthread_mutex_unlock(&philo->shared->forks[philo->first_fork]);
		return ;
	}
	timestamp = time_diff(philo->shared->start_time, current_time);
	printfast(timestamp, philo->index + 1, "has taken a fork", philo->shared->print_buffer);
	pthread_mutex_unlock(&philo->shared->log_lock);
}

static void	release_2_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->shared->forks[philo->first_fork]);
	pthread_mutex_unlock(&philo->shared->forks[philo->second_fork]);
}

// after getting the second fork,a philo can only update his last_meal
// when he has got the meal and the log locks
void	ph_get_2nd_fork_eat(t_philo *philo)
{
	struct timeval	current_time;
	long			timestamp;

	pthread_mutex_lock(&philo->shared->forks[philo->second_fork]);
	pthread_mutex_lock(&philo->meal_lock);
	pthread_mutex_lock(&philo->shared->log_lock);
	if (philo->shared->sim_over || is_dead(philo, &current_time))
	{
		pthread_mutex_unlock(&philo->shared->log_lock);
		pthread_mutex_unlock(&philo->meal_lock);
		release_2_forks(philo);
		return ;
	}
	philo->last_meal = current_time;
	timestamp = time_diff(philo->shared->start_time, current_time);
	printfast(timestamp, philo->index + 1, "has taken a fork", philo->shared->print_buffer);
	printfast(timestamp, philo->index + 1, "is eating", philo->shared->print_buffer);
	pthread_mutex_unlock(&philo->shared->log_lock);
	pthread_mutex_unlock(&philo->meal_lock);
	sleep_well(philo->params->time_to_eat);
	philo->meal_count++;
	release_2_forks(philo);
}

void	ph_sleep(t_philo *philo)
{
	struct timeval	current_time;
	long			timestamp;

	pthread_mutex_lock(&philo->shared->log_lock);
	if (philo->shared->sim_over || is_dead(philo, &current_time))
	{
		pthread_mutex_unlock(&philo->shared->log_lock);
		return ;
	}
	timestamp = time_diff(philo->shared->start_time, current_time);
	printfast(timestamp, philo->index + 1, "is sleeping", philo->shared->print_buffer);
	pthread_mutex_unlock(&philo->shared->log_lock);
	sleep_well(philo->params->time_to_sleep);
}

void	ph_think(t_philo *philo)
{
	struct timeval	current_time;
	long			timestamp;

	pthread_mutex_lock(&philo->shared->log_lock);
	if (philo->shared->sim_over || is_dead(philo, &current_time))
	{
		pthread_mutex_unlock(&philo->shared->log_lock);
		return ;
	}
	timestamp = time_diff(philo->shared->start_time, current_time);
	printf("%ld %d is thinking\n", timestamp, philo->index + 1);
	pthread_mutex_unlock(&philo->shared->log_lock);
}
