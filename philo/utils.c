/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:44:33 by khorike           #+#    #+#             */
/*   Updated: 2023/08/17 12:56:19 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi_kai(char *nptr)
{
	int	i;
	int	digit;
	int	result;

	i = 0;
	digit = 0;
	result = 0;
	while (nptr[i])
	{
		digit = nptr[i] - '0';
		if (digit < 0 || digit > 9)
		{
			write(STDERR_FILENO, ERR_DIGIT, ft_strlen(ERR_DIGIT));
			return (ERROR);
		}
		if (result > INT_MAX / 10
			|| (result == INT_MAX / 10 && digit > INT_MAX % 10))
		{
			write(STDERR_FILENO, ERR_OVERFLOW, ft_strlen(ERR_OVERFLOW));
			return (ERROR);
		}
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

void	*free_table(t_table *table)
{
	size_t	i;

	if (table == NULL)
		return (NULL);
	ft_free(table->fork_mutexes);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->philos_amount)
		{
			ft_free(table->philos[i]);
			i++;
		}
		ft_free(table->philos);
	}
	ft_free(table);
	return (NULL);
}

void	print_philosopher_status(t_philo *philo, bool died, t_status state)
{
	pthread_mutex_lock(&philo->table->output_mutex);
	if (stop_flag_status(philo->table) == true && died == false)
	{
		pthread_mutex_unlock(&philo->table->output_mutex);
		return ;
	}
	if (state == DIED)
		printf("%ld %zu %s\n", get_current_ms_time() - philo->table->start_time,
			philo->id + 1, "died");
	else if (state == EATING)
		printf("%ld %zu %s\n", get_current_ms_time() - philo->table->start_time,
			philo->id + 1, "is eating");
	else if (state == SLEEPING)
		printf("%ld %zu %s\n", get_current_ms_time() - philo->table->start_time,
			philo->id + 1, "is sleeping");
	else if (state == THINKING)
		printf("%ld %zu %s\n", get_current_ms_time() - philo->table->start_time,
			philo->id + 1, "is thinking");
	else if (state == TOOK_FORK_1 || state == TOOK_FORK_2)
		printf("%ld %zu %s\n", get_current_ms_time() - philo->table->start_time,
			philo->id + 1, "has taken a fork");
	pthread_mutex_unlock(&philo->table->output_mutex);
}

time_t	get_current_ms_time(void)
{
	struct timeval	tv;
	time_t			ms;

	if (gettimeofday(&tv, NULL))
	{
		printf("gettimodfy error\n");
		return (0);
	}
	ms = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (ms);
}
