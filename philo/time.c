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

#define SLEEP_PRECISION 50
void	sleep_well(int time_ms)
{
	struct timeval start;
	struct timeval now;
	long			elapsed_time;
	long			time_2_sleep;

	gettimeofday(&start, NULL);
	elapsed_time = 0;
	time_2_sleep = time_ms * 1000;
	while (elapsed_time < time_2_sleep)
	{
		usleep(SLEEP_PRECISION);
		gettimeofday(&now, NULL);
		elapsed_time = now.tv_sec * 1000000 + now.tv_usec - (start.tv_sec * 1000000 + start.tv_usec); 
	}
}