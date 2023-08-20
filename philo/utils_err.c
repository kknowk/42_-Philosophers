/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:58:44 by khorike           #+#    #+#             */
/*   Updated: 2023/08/15 13:58:17 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_error(char *error_str)
{
	write(STDERR_FILENO, error_str, ft_strlen(error_str));
	write(STDERR_FILENO, "\n", 1);
	return ;
}

void	*perr_return_null(char *error_str)
{
	write(STDERR_FILENO, error_str, ft_strlen(error_str));
	write(STDERR_FILENO, "\n", 1);
	return (NULL);
}

void	ft_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	return ;
}
