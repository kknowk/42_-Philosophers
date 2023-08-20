/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:00:12 by khorike           #+#    #+#             */
/*   Updated: 2023/08/17 15:23:13 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_validity_of_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, ERR_WRONG_NUM_ARGS, ft_strlen(ERR_WRONG_NUM_ARGS));
		return (false);
	}
	while (i < argc)
	{
		if (i == 1 && (ft_atoi_kai(argv[i]) == 0 || ft_atoi_kai(argv[i]) > 250))
		{
			put_error(ERR_PHILOS_RANGE);
			return (false);
		}
		if (ft_atoi_kai(argv[i]) == ERROR)
			return (false);
		i++;
	}
	return (true);
}

static bool	start_simulation(t_table *table)
{
	size_t	i;

	table->start_time = get_current_ms_time() + (table->philos_amount * 20);
	i = 0;
	while (i < table->philos_amount)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				&philosopher_routine, table->philos[i]) != 0)
			return (false);
		i++;
	}
	if (table->philos_amount > 1)
	{
		if (pthread_create(&table->philo_death, NULL,
				&death_simulation, table) != 0)
			return (false);
	}
	return (true);
}

static void	destroy_mutexes(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_amount)
	{
		pthread_mutex_destroy(&table->fork_mutexes[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->output_mutex);
	pthread_mutex_destroy(&table->stop_status_mutex);
}

static void	stop_simulation(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_amount)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->philos_amount > 1)
		pthread_join(table->philo_death, NULL);
	destroy_mutexes(table);
	free_table(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (check_validity_of_args(argc, argv) == false)
		return (FAILURE);
	table = init_table(argc, argv);
	if (table == NULL)
		return (FAILURE);
	if (start_simulation(table) == false)
	{
		put_error(ERR_THREAD_CREATION);
		return (FAILURE);
	}
	stop_simulation(table);
	return (SUCCESS);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q philo");
// }
