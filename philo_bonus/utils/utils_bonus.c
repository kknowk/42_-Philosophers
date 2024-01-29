/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:44:33 by khorike           #+#    #+#             */
/*   Updated: 2024/01/29 12:45:01 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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

static void	*ft_memset(void *buf, int ch, size_t n)
{
	size_t			i;
	unsigned char	*buf_set;

	buf_set = (unsigned char *)buf;
	i = 0;
	while (i < n)
	{
		buf_set[i] = (unsigned char)ch;
		i++;
	}
	return (buf);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*pmem;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (count > SIZE_MAX / size)
		exit(EXIT_FAILURE);
	pmem = malloc(count * size);
	if (pmem == NULL)
	{
		write(STDERR_FILENO, ERR_MALLOC_FAIL, ft_strlen(ERR_MALLOC_FAIL));
		exit(1);
	}
	ft_memset(pmem, 0, count * size);
	return (pmem);
}

void	cleanup(sem_t **forks, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		sem_close(forks[i]);
		i++;
	}
	free(forks);
}
