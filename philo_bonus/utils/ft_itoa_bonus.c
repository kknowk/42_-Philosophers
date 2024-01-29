/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:52:47 by khorike           #+#    #+#             */
/*   Updated: 2024/01/29 12:52:56 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static int	check_digit(int n, size_t digit)
{
	if (n < 0)
	{
		n /= 10;
		return (check_digit(n, digit + 1));
	}
	if (n < 10)
		return (digit + 1);
	return (check_digit(n / 10, digit + 1));
}

char	*ft_itoa(int n)
{
	size_t	digit;
	char	*nbr;
	char	*p;

	digit = check_digit(n, 0);
	nbr = ft_calloc(sizeof(char), (digit + 1));
	p = nbr + digit;
	*p = '\0';
	if (n <= 0)
	{
		*nbr = '-';
		*--p = -(n % 10) + '0';
		n /= -10;
	}
	while (n != 0)
	{
		*--p = n % 10 + '0';
		n /= 10;
	}
	return (nbr);
}
