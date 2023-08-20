/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:22:20 by khorike           #+#    #+#             */
/*   Updated: 2023/08/20 17:44:03 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat(t_philo *p, struct timeval *start_time)
{
	p->meals_eaten++;
	gettimeofday(&p->last_meal_time, NULL);
	printf("%ld %d is eating\n", get_elapsed_time_ms(start_time), p->id + 1);
	my_usleep(p->time_to_eat * 1000);
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
	if (get_elapsed_time_ms(&p->last_meal_time) >= p->time_to_die)
	{
		printf("%ld %d died\n", get_elapsed_time_ms(start_time), p->id + 1);
		exit(1);
	}
}

void	philosopher(t_philo *p)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	gettimeofday(&p->last_meal_time, NULL);
	while (1)
	{
		check_death(p, &start_time);
		take_forks(p, &start_time);
		eat(p, &start_time);
		release_forks(p);
		sleep_and_think(p, &start_time);
		if (p->times_to_eat > 0 && p->meals_eaten >= p->times_to_eat)
		{
			exit(2);
		}
	}
}
