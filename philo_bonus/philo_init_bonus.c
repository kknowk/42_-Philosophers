/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:06:05 by khorike           #+#    #+#             */
/*   Updated: 2023/08/20 17:49:52 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	initialize(int number_of_philosophers,
			sem_t ***forks, t_philo *philosophers)
{
	char	sem_name[16];
	sem_t	*fork_sem;
	int		i;

	*forks = ft_malloc(sizeof(sem_t *) * number_of_philosophers);
	i = 0;
	while (i < number_of_philosophers)
	{
		fork_sem = sem_open(sem_name, O_CREAT, 0666, 1);
		if (fork_sem == SEM_FAILED)
			exit(EXIT_FAILURE);
		(*forks)[i] = fork_sem;
		sem_unlink(sem_name);
		i++;
	}
	i = 0;
	while (i < number_of_philosophers)
	{
		philosophers[i].id = i;
		philosophers[i].left_fork = (*forks)[i];
		philosophers[i].right_fork = (*forks)[(i + 1) % number_of_philosophers];
		philosophers[i].meals_eaten = 0;
		i++;
	}
}
