/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:54:55 by khorike           #+#    #+#             */
/*   Updated: 2023/08/20 15:00:06 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_elapsed_time_ms(struct timeval *start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - start_time->tv_sec) * 1000 + \
			(current_time.tv_usec - start_time->tv_usec) / 1000);
}

static long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000000 + tv.tv_usec;
	return (time);
}

static long	get_time_diff(long long start)
{
	long	diff;

	diff = get_time() - start;
	return (diff);
}

void	my_usleep(long action_time)
{
	long	start;

	start = get_time();
	while (get_time_diff(start) < action_time)
		usleep(100);
}
