#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

// # define DELTA 0
# define BUFFER_SIZE 50

typedef struct	s_shared_mem
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_lock;
	char			print_buffer[BUFFER_SIZE];
	struct timeval	start_time;
	int				sim_over;
	int				start;
}				t_shared_mem;

typedef struct	s_params
{
	int		time_to_eat;
	int		time_to_sleep;
	int		n_philos;
	int		time_to_die;
	int		meals_2_eat;
}				t_params;

typedef struct	s_philo
{
	int				index;
	struct timeval	last_meal;
	pthread_mutex_t	meal_lock;
	int				first_fork;
	int				second_fork;
	int				meal_count;
	t_shared_mem	*shared;
	t_params		*params;
	pthread_t		thread_id;
}				t_philo;


int		parse_params(int argc, char **argv, t_params *params);
int		setup(t_params *params, t_shared_mem *shared, t_philo **philos);

void	ph_get_first_fork(t_philo *philo);
void	ph_get_2nd_fork_eat(t_philo *philo);
void	ph_sleep(t_philo *philo);
void	ph_think(t_philo *philo);

int		is_dead(t_philo *philo, struct timeval *time_of_check);
long	time_diff(struct timeval t1, struct timeval t2);

void	check_4_deaths(t_philo *philos, t_params *params, t_shared_mem *shared);
void	check_n_meals(t_philo *philos, t_params *params, t_shared_mem *shared);
void	destroy_locks_array(pthread_mutex_t *array, int n);
void	clear_memory(t_philo *philos, t_shared_mem *shared, int n_philos);


void	switch_forks(t_philo *philo);
void	sleep_well(int time_ms);
void	printfast(long timestamp, int philo_id, char *action, char *buffer);

#endif
