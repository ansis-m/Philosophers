/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:33:50 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/07 11:42:01 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<sys/types.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_philo
{
	long long		begin;
	long long		last_meal;
	long long		marker;
	pid_t			*pids;
	sem_t			*forks;
	int				*alive;
	int				number;
	int				total;
	int				tdie;
	int				teat;
	int				tsleep;
	int				meals;
}	t_philo;

//main_bonus.c
int			philo(t_philo	*philosophers, int i);

//ft_atoi.c
int			ft_atoi(const char *nptr);

//basic_utils.c
void		deallocate(t_philo *philosophers, pid_t	*pids);
int			check_args(int argc, char *argv[], int args[6]);
int			aloc_pointers(t_philo **philosophers, pid_t	**pids, int size);
long long	get_time_now(void);
long long	timestamp(long long begin);

//fork_utils.c
void		init_args(t_philo *philosophers, int args[6], int i);
void		init_philosophers(t_philo *philosophers,
				sem_t *forks, pid_t *pids, int args[6]);
void		fork_kids(pid_t *pids, t_philo *philosophers, int size);
void		terminate(pid_t *pids, int size);
void		wait_kids(pid_t *pids, int size);

//philo_cycle_utils.c
void		delay(t_philo *data, int multiplier);
int			initial_delay(t_philo *data);
bool		still_alive(t_philo *philosopher);
int			lock_second_fork(t_philo *data);
int			lock_first_fork(t_philo *data);

//philo_cycle_utils2.c
int			eat(t_philo *data);
void		go_to_sleep(t_philo *data, long long marker);

#endif
