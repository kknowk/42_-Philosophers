/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:12:18 by khorike           #+#    #+#             */
/*   Updated: 2024/01/29 14:22:10 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static void	start_philosophers(t_philo *philosophers,
			pid_t *pids, char *argv[], int argc)
{
	int		number_of_philosophers;
	int		i;
	pid_t	pid;

	i = 0;
	number_of_philosophers = ft_atoi_kai(argv[1]);
	while (i < number_of_philosophers)
	{
		philosophers[i].time_to_die = ft_atoi_kai(argv[2]);
		philosophers[i].time_to_eat = ft_atoi_kai(argv[3]);
		philosophers[i].time_to_sleep = ft_atoi_kai(argv[4]);
		if (argc > 5)
			philosophers[i].times_to_eat = ft_atoi_kai(argv[5]);
		else
			philosophers[i].times_to_eat = -1;
		pid = fork();
		if (pid == 0)
		{
			philosopher(&philosophers[i]);
			exit(0);
		}
		else
			pids[i] = pid;
		i++;
	}
}

static void	lonely_philo(int number_of_philosophers, char *argv[])
{
	if (number_of_philosophers == 1)
	{
		printf("0 1 has taken a fork\n");
		my_usleep(ft_atoi_kai(argv[2]) * 1000);
		printf("%d 1 died\n", ft_atoi_kai(argv[2]));
		exit(1);
	}
	return ;
}

static	void	wait_kill(int number_of_philosophers)
{
	int		i;
	int		status;

	i = 0;
	while (i < number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				kill(0, SIGTERM);
			}
			else if (WEXITSTATUS(status) == 2)
				i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	int		number_of_philosophers;
	t_philo	*philosophers;
	sem_t	**forks;
	pid_t	*pids;

	if (check_validity_of_args(argc, argv) == false)
		return (FAILURE);
	number_of_philosophers = ft_atoi_kai(argv[1]);
	lonely_philo(number_of_philosophers, argv);
	philosophers = ft_calloc(sizeof(t_philo), number_of_philosophers);
	initialize(number_of_philosophers, &forks, philosophers);
	pids = ft_calloc(sizeof(pid_t), number_of_philosophers);
	start_philosophers(philosophers, pids, argv, argc);
	wait_kill(number_of_philosophers);
	cleanup(forks, number_of_philosophers);
	free(philosophers);
	free(pids);
	return (0);
}
