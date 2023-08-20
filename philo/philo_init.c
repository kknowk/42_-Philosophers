/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:08:48 by khorike           #+#    #+#             */
/*   Updated: 2023/08/17 12:57:26 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->philos_amount;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->philos_amount;
		philo->fork[1] = philo->id;
	}
}

static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	size_t			i;

	forks = malloc(sizeof(pthread_mutex_t) * table->philos_amount);
	if (forks == NULL)
		return (perr_return_null(ERR_MALLOC_FAIL));
	i = 0;
	while (i < table->philos_amount)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (perr_return_null(ERR_MUTEX_INIT_FAIL));
		i++;
	}
	return (forks);
}

static t_philo	**init_philos(t_table *table)
{
	t_philo			**philos;
	size_t			i;

	philos = malloc(sizeof(t_philo *) * table->philos_amount);
	if (philos == NULL)
		return (perr_return_null(ERR_MALLOC_FAIL));
	i = 0;
	while (i < table->philos_amount)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
		{
			ft_free(philos);
			return (perr_return_null(ERR_MALLOC_FAIL));
		}
		if (pthread_mutex_init(&philos[i]->meal_time_mutex, 0) != 0)
			return (perr_return_null(ERR_MUTEX_INIT_FAIL));
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->ate_count = 0;
		philos[i]->last_meal = get_current_ms_time();
		set_forks(philos[i]);
		i++;
	}
	return (philos);
}

static bool	init_mutexes(t_table *table)
{
	table->fork_mutexes = init_forks(table);
	if (table->fork_mutexes == NULL)
		return (false);
	if (pthread_mutex_init(&table->stop_status_mutex, 0) != 0)
	{
		put_error(ERR_MUTEX_INIT_FAIL);
		return (false);
	}
	if (pthread_mutex_init(&table->output_mutex, 0) != 0)
	{
		put_error(ERR_MUTEX_INIT_FAIL);
		return (false);
	}
	return (true);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (table == NULL)
		return (perr_return_null(ERR_MALLOC_FAIL));
	table->philos_amount = ft_atoi_kai(argv[PHILO_COUNT]);
	table->time_to_die = ft_atoi_kai(argv[DIE_TIME]);
	table->time_to_eat = ft_atoi_kai(argv[EAT_TIME]);
	table->time_to_sleep = ft_atoi_kai(argv[SLEEP_TIME]);
	table->must_eat_count = -1;
	if (argc == 6)
		table->must_eat_count = ft_atoi_kai(argv[MEALS_COUNT]);
	table->philos = init_philos(table);
	if (table->philos == NULL)
		return (free_table(table));
	if (init_mutexes(table) == false)
		return (free_table(table));
	table->stop_status = false;
	return (table);
}
