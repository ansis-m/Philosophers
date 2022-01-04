/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:33:50 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/04 16:33:20 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdbool.h>
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
	pthread_mutex_t	*death_checker_lock;
	pthread_mutex_t	*indicator_lock;
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
void		delay(t_philo *data, int multiplier);
int			initial_delay(t_philo *data);
int			philo_cycle(t_philo *data, long long sleep);

//philosopher_threads_utils.c
int			lock_second_fork(t_philo *data);
int			lock_first_fork(t_philo *data);
int			eat(t_philo *data);
int			has_died(t_philo *data);
void		go_to_sleep(t_philo *data, long long marker);

//death_checker_threads.c
bool		still_alive(t_philo *philosopher);
int			start_death_checker_threads(pthread_t *threads,
				t_philo *philosophers, int size);
int			init_death_checker_locks(pthread_mutex_t **death_checker_locks,
				int size);
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
