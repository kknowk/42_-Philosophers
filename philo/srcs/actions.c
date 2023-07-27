/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:49:18 by khorike           #+#    #+#             */
/*   Updated: 2023/07/27 19:15:19 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_take_forks(t_data *data, t_philo *phi)
{
	(void)data;
	if (data->philo_num == 1)
	{
		pthread_mutex_lock(phi->l_fork);
		printf("%llu %d has taken a fork\n", get_time_ms(), phi->id);
	}
	else if (phi->id % 2 == 0)
	{
		pthread_mutex_lock(phi->r_fork);
		pthread_mutex_lock(phi->l_fork);
	}
	else
	{
		pthread_mutex_lock(phi->l_fork);
		pthread_mutex_lock(phi->r_fork);
	}
	printf("%llu %d has taken a fork\n", get_time_ms(), phi->id);
}

static void	ft_eat(t_data *data, t_philo *phi)
{
	pthread_mutex_lock(&phi->lock);
	printf("%llu %d is eating\n", get_time_ms(), phi->id);
	usleep(data->eat_time * 1000);
	phi->time_to_die = get_time_ms();
	phi->eat_cont++;
	pthread_mutex_unlock(&phi->lock);
}

static void	ft_sleep(t_data *data, t_philo *phi)
{
	printf("%llu %d is sleeping\n", get_time_ms(), phi->id);
	usleep(data->sleep_time * 1000);
}

static void	ft_think(t_data *data, t_philo *phi)
{
	(void)data;
	printf("%llu %d is thinking\n", get_time_ms(), phi->id);
}

void	*life_cycle(void *arg)
{
	t_philo		*phi;
	t_data		*data;
	pthread_t	death_checker;

	phi = (t_philo *)arg;
	data = phi->data;
	if (pthread_create(&death_checker, NULL, death_check, phi))
		return (p_error("Error: could not create death_checker thread\n"));
	while (1)
	{
		// pthread_mutex_lock(&data->dead_mutex);
		if (is_dead(data))
		{
			// pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		ft_take_forks(data, phi);
		ft_eat(data, phi);
		pthread_mutex_unlock(phi->l_fork);
		pthread_mutex_unlock(phi->r_fork);
		ft_sleep(data, phi);
		ft_think(data, phi);
		if (has_eaten_enough(data, phi))
			break ;
	}
	pthread_join(death_checker, NULL);
	return (NULL);
}
