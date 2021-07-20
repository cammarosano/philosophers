/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:23:36 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/20 20:23:37 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	printfast(timestamp, philo, "has taken a fork");
	pthread_mutex_unlock(&philo->shared->log_lock);
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
		pthread_mutex_unlock(&philo->shared->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->shared->forks[philo->second_fork]);
		return ;
	}
	philo->last_meal = current_time;
	timestamp = time_diff(philo->shared->start_time, current_time);
	printfast(timestamp, philo, "has taken a fork");
	printfast(timestamp, philo, "is eating");
	pthread_mutex_unlock(&philo->shared->log_lock);
	pthread_mutex_unlock(&philo->meal_lock);
	sleep_well(philo->params->time_to_eat);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->shared->forks[philo->first_fork]);
	pthread_mutex_unlock(&philo->shared->forks[philo->second_fork]);
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
	printfast(timestamp, philo, "is sleeping");
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
	printfast(timestamp, philo, "is thinking");
	pthread_mutex_unlock(&philo->shared->log_lock);
}
