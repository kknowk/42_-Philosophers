/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:21 by khorike           #+#    #+#             */
/*   Updated: 2023/08/19 16:51:19 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_routine(t_table *table, time_t sleep_time)
{
	time_t	awake;

	awake = get_current_ms_time() + sleep_time;
	while (get_current_ms_time() < awake)
	{
		if (stop_flag_status(table))
			break ;
		usleep(100);
	}
}

static void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_mutexes[philo->fork[0]]);
	print_philosopher_status(philo, false, TOOK_FORK_1);
	pthread_mutex_lock(&philo->table->fork_mutexes[philo->fork[1]]);
	print_philosopher_status(philo, false, TOOK_FORK_2);
	print_philosopher_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal = get_current_ms_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	sleep_routine(philo->table, philo->table->time_to_eat);
	if (stop_flag_status(philo->table) == false)
	{
		pthread_mutex_lock(&philo->meal_time_mutex);
		philo->ate_count++;
		pthread_mutex_unlock(&philo->meal_time_mutex);
	}
	print_philosopher_status(philo, false, SLEEPING);
	pthread_mutex_unlock(&philo->table->fork_mutexes[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_mutexes[philo->fork[0]]);
	sleep_routine(philo->table, philo->table->time_to_sleep);
}

static void	think_routine(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_mutex);
	time_to_think = (philo->table->time_to_die
			- (get_current_ms_time() - philo->last_meal)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		print_philosopher_status(philo, false, THINKING);
	sleep_routine(philo->table, time_to_think);
}

static void	*lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_mutexes[philo->fork[0]]);
	print_philosopher_status(philo, false, TOOK_FORK_1);
	sleep_routine(philo->table, philo->table->time_to_die);
	print_philosopher_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->table->fork_mutexes[philo->fork[0]]);
	return (NULL);
}

void	*philosopher_routine(void *table_data)
{
	t_philo	*philo;

	philo = (t_philo *)table_data;
	if (philo->table->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	while (get_current_ms_time() < philo->table->start_time)
		continue ;
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->philos_amount == 1)
		return (lonely_philo(philo));
	else if (philo->id % 2)
		think_routine(philo, true);
	while (stop_flag_status(philo->table) == false)
	{
		eat_sleep_routine(philo);
		think_routine(philo, false);
	}
	return (NULL);
}
