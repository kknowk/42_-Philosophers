/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:22:20 by khorike           #+#    #+#             */
/*   Updated: 2024/01/29 15:04:13 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat(t_philo *p, struct timeval *start_time)
{
	p->meals_eaten++;
	printf("%ld %d is eating\n", get_elapsed_time_ms(start_time), p->id + 1);
	if (get_elapsed_time_ms(start_time) - p->last_meal_time + p->time_to_eat > p->time_to_die)
	{
		my_usleep((p->time_to_die - get_elapsed_time_ms(start_time))  * 1000);
		printf("%ld %d died\n", get_elapsed_time_ms(start_time), p->id + 1);
		exit(1);
	}
	my_usleep(p->time_to_eat * 1000);
	p->last_meal_time = get_elapsed_time_ms(start_time);
}

static void	sleep_and_think(t_philo *p, struct timeval *start_time)
{
	printf("%ld %d is sleeping\n", get_elapsed_time_ms(start_time), p->id + 1);
	my_usleep(p->time_to_sleep * 1000);
	if (p->meals_eaten <= p->times_to_eat)
		printf("%ld %d is thinking\n",
			get_elapsed_time_ms(start_time), p->id + 1);
	my_usleep(1000);
}

static void	check_death(t_philo *p, struct timeval *start_time)
{
	if (get_elapsed_time_ms(start_time) - p->last_meal_time >= p->time_to_die)
	{
		printf("%ld %d died\n", get_elapsed_time_ms(start_time), p->id + 1);
		exit(1);
	}
}

void	philosopher(t_philo *p)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	p->last_meal_time = 0;
	while (1)
	{
		check_death(p, &start_time);
		take_forks(p, &start_time);
		eat(p, &start_time);
		check_death(p, &start_time);
		release_forks(p);
		sleep_and_think(p, &start_time);
		if (p->times_to_eat > 0 && p->meals_eaten >= p->times_to_eat)
		{
			exit(2);
		}
	}
}
