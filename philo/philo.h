/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:33:50 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/03 12:24:04 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<limits.h> // TO BE REMOVED????????
# include	<sys/types.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	long long		begin;
	long long		last_meal;
	long long		marker;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	int				*alive;
	int				number;
	int				total;
	int				tdie;
	int				teat;
	int				tsleep;
	int				meals;
}	t_philo;

//main.c

//philosopher_threads.c
int			start_threads(pthread_t *threads, t_philo *philosophers, int size);
void		*philosopher(void *philo_data);

//death_checker_threads.c
int			start_death_checker_threads(pthread_t *threads,
				t_philo *philosophers, int size);
void		*death_checker(void *philo_data);

//ft_atoi.c
int			ft_atoi(const char *nptr);

//basic_utils.c
void		deallocate(pthread_mutex_t *forks,
				pthread_mutex_t *death_checker_locks,
				t_philo *p, pthread_t *threads);
void		init_forks(pthread_mutex_t *forks, int args);
void		destroy_forks(pthread_mutex_t *forks, int args);
int			check_args(int argc, char *argv[], int args[6]);
int			aloc_pointers(pthread_mutex_t **forks,
				t_philo **philosophers, pthread_t **threads, int size);

//basic_utils2.c
int			join_threads(pthread_t *threads, int size);
long long	get_time_now(void);
long long	timestamp(long long begin);

#endif
