#include "philo.h"

// general principles: for every action (take a fork, eat, sleep, think),
// once the philo has got the LOG lock, he checks whether he's not dead and
// if the simulation is not over (due to someone else's death)
void	ph_get_first_fork(t_philo *philo)
{
	struct timeval	current_time;
	long			timestamp;

	// get fork
	pthread_mutex_lock(&philo->shared->forks[philo->first_fork]);
	// get log_lock
	pthread_mutex_lock(&philo->shared->log_lock);
	// once log_lock is taken verify if sim over or if dead 
	if (philo->shared->sim_over || is_dead(philo, &current_time)) // if so, drop fork and log lock and return
	{
		pthread_mutex_unlock(&philo->shared->log_lock);
		pthread_mutex_unlock(&philo->shared->forks[philo->first_fork]);
		return ;
	}
	timestamp = time_diff(philo->shared->start_time, current_time);
	printfast(timestamp, philo->index + 1, "has taken a fork", philo->shared->print_buffer);
	// printf("%ld %d has taken a fork\n", timestamp, philo->index + 1);
	pthread_mutex_unlock(&philo->shared->log_lock);
}

static void	release_2_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->shared->forks[philo->first_fork]);
	pthread_mutex_unlock(&philo->shared->forks[philo->second_fork]);
}

// a philo can only update his last_meal (start eating) when he has got
// two forks AND the log lock
void	ph_get_2nd_fork_eat(t_philo *philo)
{
	struct timeval	current_time;
	long			timestamp;

	// get second fork
	pthread_mutex_lock(&philo->shared->forks[philo->second_fork]);
	// get log lock
	pthread_mutex_lock(&philo->meal_lock); //
	pthread_mutex_lock(&philo->shared->log_lock);
	// check if not over
	if (philo->shared->sim_over || is_dead(philo, &current_time))
	{
		pthread_mutex_unlock(&philo->shared->log_lock);
		pthread_mutex_unlock(&philo->meal_lock); //
		release_2_forks(philo);
		return ;
	}
	// update last meal and log
	philo->last_meal = current_time;
	timestamp = time_diff(philo->shared->start_time, current_time);
	printfast(timestamp, philo->index + 1, "has taken a fork", philo->shared->print_buffer);
	// printf("%ld %d has taken a fork\n", timestamp, philo->index + 1);
	printfast(timestamp, philo->index + 1, "is eating", philo->shared->print_buffer);
	// printf("%ld %d is eating\n", timestamp, philo->index + 1);
	// release log lock
	pthread_mutex_unlock(&philo->shared->log_lock);
	pthread_mutex_unlock(&philo->meal_lock); //
	// spend time eating
	// usleep(philo->params->time_to_eat * 1000);
	sleep_well(philo->params->time_to_eat);
	// update meal count and release forks
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
	// printf("%ld %d is sleeping\n", timestamp, philo->index + 1);
	pthread_mutex_unlock(&philo->shared->log_lock);
	// usleep(philo->params->time_to_sleep * 1000);
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
	// printfast(timestamp, philo->index + 1, "is thinking", philo->shared->print_buffer);
	printf("%ld %d is thinking\n", timestamp, philo->index + 1);
	pthread_mutex_unlock(&philo->shared->log_lock);
}
