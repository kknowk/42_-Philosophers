/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:22:54 by khorike           #+#    #+#             */
/*   Updated: 2023/08/17 12:58:26 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->stop_status_mutex);
	table->stop_status = state;
	pthread_mutex_unlock(&table->stop_status_mutex);
}

bool	stop_flag_status(t_table *table)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&table->stop_status_mutex);
	if (table->stop_status == true)
		result = true;
	pthread_mutex_unlock(&table->stop_status_mutex);
	return (result);
}

static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_current_ms_time();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		set_stop_flag(philo->table, true);
		print_philosopher_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_mutex);
		return (true);
	}
	return (false);
}

static bool	end_condition_reached(t_table *table)
{
	size_t			i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->philos_amount)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_mutex);
		if (kill_philo(table->philos[i]))
			return (true);
		if (table->must_eat_count != -1)
			if (table->philos[i]->ate_count
				< (unsigned int)table->must_eat_count)
				all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->meal_time_mutex);
		i++;
	}
	if (table->must_eat_count != -1 && all_ate_enough == true)
	{
		set_stop_flag(table, true);
		return (true);
	}
	return (false);
}

void	*death_simulation(void *table_data)
{
	t_table			*table;

	table = (t_table *)table_data;
	if (table->must_eat_count == 0)
		return (NULL);
	set_stop_flag(table, false);
	while (get_current_ms_time() < table->start_time)
		continue ;
	while (true)
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
