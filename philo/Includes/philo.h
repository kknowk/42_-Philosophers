/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:00:52 by khorike           #+#    #+#             */
/*   Updated: 2023/07/26 19:27:10 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>

# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/gnl/get_next_line.h"

# define FAILURE 1
# define SUCCESS 0
# define ERROR -1

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finished;
	t_philo			*philos;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	finished_mutex;
}	t_data;

void		*life_cycle(void *arg);

int			has_eaten_enough(t_data *data, t_philo *phi);
int			is_dead(t_data *data);
uint64_t	get_time_ms(void);
void		*death_check(void *arg);

void		*p_error(char *str);
int			ft_atoi_kai(char *nptr);

int			check_argc(int argc, char **argv);

#endif