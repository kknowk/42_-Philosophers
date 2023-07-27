/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_life_cycle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:08:38 by khorike           #+#    #+#             */
/*   Updated: 2023/07/27 19:27:28 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_eaten_enough(t_data *data, t_philo *phi)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&data->finished_mutex);
	if (data->meals_nb != -1 && phi->eat_cont >= data->meals_nb)
	{
		data->finished++;
		if (data->finished == data->philo_num)
		{
			pthread_mutex_lock(&data->dead_mutex);
			printf("eat locked %d\n", phi->id);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			printf("eat unlocked %d\n", phi->id);
		}
		result = 1;
	}
	pthread_mutex_unlock(&data->finished_mutex);
	return (result);
}

int	is_dead(t_data *data)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&data->dead_mutex);
	if (data->dead)
	{
		result = 1;
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (result);
}

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("gettimodfy error\n");
		return (0);
	}
	return ((uint64_t)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*death_check(void *arg)
{
	t_philo	*phi;
	t_data	*data;

	phi = (t_philo *)arg;
	data = phi->data;
	while (1)
	{
		pthread_mutex_lock(&phi->data->dead_mutex);
		if (phi->data->dead
			|| get_time_ms() - phi->time_to_die > phi->data->death_time)
		{
			if (!phi->data->dead)
			{
				printf("%llu %d died\n", get_time_ms(), phi->id);
				phi->data->dead = 1;
			}
			pthread_mutex_unlock(&phi->data->dead_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&phi->data->dead_mutex);
		usleep(10);
	}
	return (NULL);
}
