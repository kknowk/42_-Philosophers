/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:00:12 by khorike           #+#    #+#             */
/*   Updated: 2023/07/27 19:27:52 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_data(t_data *data, int argc, char **argv)
{
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->finished_mutex, NULL);
	data->philo_num = ft_atoi_kai(argv[1]);
	data->death_time = ft_atoi_kai(argv[2]);
	data->eat_time = ft_atoi_kai(argv[3]);
	data->sleep_time = ft_atoi_kai(argv[4]);
	if (argc == 6)
		data->meals_nb = ft_atoi_kai(argv[5]);
	else
		data->meals_nb = -1;
	data->dead = 0;
	data->finished = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (FAILURE);
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
	{
		free(data->forks);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->philo_num];
		data->philos[i].eat_cont = 0;
		data->philos[i].time_to_die = get_time_ms();
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

static int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].t1, NULL,
				life_cycle, &data->philos[i]) != 0)
		{
			printf("Error: could not create philosopher thread\n");
			return (FAILURE);
		}
		pthread_detach(data->philos[i].t1);
		i++;
	}
	return (SUCCESS);
}

static void	end_program(t_data *data)
{
	free(data->philos);
	free(data->forks);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_argc(argc, argv))
		return (FAILURE);
	if (init_data(&data, argc, argv) == FAILURE)
		return (FAILURE);
	init_philosophers(&data);
	if (start_threads(&data) == FAILURE)
		return (FAILURE);
	while (1)
	{
		pthread_mutex_lock(&data.dead_mutex);
		if (data.dead)
		{
			pthread_mutex_unlock(&data.dead_mutex);
			end_program(&data);
			break ;
		}
		pthread_mutex_unlock(&data.dead_mutex);
		usleep(10);
	}
	return (SUCCESS);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q philo");
// }
