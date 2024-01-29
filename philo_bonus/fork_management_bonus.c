/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:19:48 by khorike           #+#    #+#             */
/*   Updated: 2024/01/29 13:46:51 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philo *p, struct timeval *start_time)
{
	if (p->id % 2 == 0)
	{
		sem_wait(p->left_fork);
		sem_wait(p->right_fork);
		printf("%ld %d has taken a fork\n",
			get_elapsed_time_ms(start_time), p->id + 1);
		printf("%ld %d has taken a fork\n",
			get_elapsed_time_ms(start_time), p->id + 1);
	}
	else
	{
		usleep(200);
		sem_wait(p->right_fork);
		sem_wait(p->left_fork);
		printf("%ld %d has taken a fork\n",
			get_elapsed_time_ms(start_time), p->id + 1);
		printf("%ld %d has taken a fork\n",
			get_elapsed_time_ms(start_time), p->id + 1);
	}
}

void	release_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		sem_post(p->left_fork);
		sem_post(p->right_fork);
	}
	else
	{
		sem_post(p->right_fork);
		sem_post(p->left_fork);
	}
}
