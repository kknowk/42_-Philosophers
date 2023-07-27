/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:44:33 by khorike           #+#    #+#             */
/*   Updated: 2023/07/26 19:26:35 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_error(char *str)
{
	printf("%s\n", str);
	return (0);
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
			write(STDERR_FILENO, "digit error\n", 12);
			return (ERROR);
		}
		if (result > INT_MAX / 10
			|| (result == INT_MAX / 10 && digit > INT_MAX % 10))
		{
			write(STDERR_FILENO, "overflow error\n", 15);
			return (ERROR);
		}
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

int	check_argc(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (FAILURE);
	}
	while (i < argc)
	{
		if (ft_atoi_kai(argv[i]) <= 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
