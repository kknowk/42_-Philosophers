/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:00:52 by khorike           #+#    #+#             */
/*   Updated: 2023/08/17 12:56:39 by khorike          ###   ########.fr       */
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

# define FAILURE 1
# define SUCCESS 0
# define ERROR -1

# define MAX_PHILOS	250

# define ERR_THREAD_CREATION "Error: Failed to create a thread\n"
# define ERR_WRONG_NUM_ARGS "Error: Wrong number of arguments\n"
# define ERR_DIGIT "Error: Invalid digit\n"
# define ERR_OVERFLOW "Error: Number overflow\n"
# define ERR_PHILOS_RANGE "Error: Enter between 1 and 250 philosophers\n"
# define ERR_MALLOC_FAIL "Error: Memory allocation failed\n"
# define ERR_MUTEX_INIT_FAIL "Error: Mutex init failed\n"

typedef enum e_params
{
	PHILO_COUNT = 1,
	DIE_TIME = 2,
	EAT_TIME = 3,
	SLEEP_TIME = 4,
	MEALS_COUNT = 5
}	t_params;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	TOOK_FORK_1 = 4,
	TOOK_FORK_2 = 5
}	t_status;

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	size_t			philos_amount;
	pthread_t		philo_death;
	int				must_eat_count;
	bool			stop_status;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	stop_status_mutex;
	pthread_mutex_t	output_mutex;
	t_philo			**philos;
}	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	size_t				fork[2];
	size_t				id;
	size_t				ate_count;
	pthread_mutex_t		meal_time_mutex;
	time_t				last_meal;
	t_table				*table;
}	t_philo;

void			*free_table(t_table *table);
// void			destroy_mutexes(t_table *table);
size_t			ft_strlen(const char *s);
int				ft_atoi_kai(char *nptr);
time_t			get_current_ms_time(void);
void			print_philosopher_status(t_philo *philo,
					bool died, t_status state);

t_table			*init_table(int argc, char **argv);
void			*philosopher_routine(void *table_data);
void			sleep_routine(t_table *table, time_t sleep_time);
void			*death_simulation(void *table_data);
bool			stop_flag_status(t_table *table);

void			*perr_return_null(char *error_str);
void			put_error(char *error_str);
void			ft_free(void *ptr);

#endif