#include "philo.h"

// returns elapsed time from t1 to t2, in ms 
long	time_diff(struct timeval t1, struct timeval t2)
{
	long	diff;

	diff = (t2.tv_sec - t1.tv_sec) * 1000;
	diff += (t2.tv_usec - t1.tv_usec) / 1000;
	return (diff);
}

// check if philo is dead (1 if yes)
// if time_of_check is not NULL, it gets updated with the time when
// the check was made
int	is_dead(t_philo *philo, struct timeval *time_of_check)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (time_of_check)
		*time_of_check = current_time;
	if (time_diff(philo->last_meal, current_time) >= philo->params->time_to_die)
		return (1);
	return (0);
}
