/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:00:52 by khorike           #+#    #+#             */
/*   Updated: 2024/01/29 15:04:08 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>

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

typedef struct s_philo{
	int				id;
	sem_t			*left_fork;
	sem_t			*right_fork;
	int				meals_eaten;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	long			last_meal_time;
}	t_philo;

// fork_management
void			take_forks(t_philo *p, struct timeval *start_time);
void			release_forks(t_philo *p);

void			philosopher(t_philo *p);

// ./utils

// time_management
void			my_usleep(long action_time);
long			get_elapsed_time_ms(struct timeval *start_time);

void			initialize(int number_of_philosophers,
					sem_t ***forks, t_philo *philosophers);

// utils
size_t			ft_strlen(const char *s);
int				ft_atoi_kai(char *nptr);
void			*ft_calloc(size_t count, size_t size);
void			cleanup(sem_t **forks, int number_of_philosophers);

// utils_err
void			*perr_return_null(char *error_str);
void			put_error(char *error_str);
void			ft_free(void *ptr);

// ft_itoa
char			*ft_itoa(int n);


char	*ft_snprintf(char *str, int n);

#endif