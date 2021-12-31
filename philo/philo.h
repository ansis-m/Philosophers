/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:33:50 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/31 18:24:30 by amalecki         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	int				total;
	char			*state;
	bool			change;
	int				*held_by;
	int				*prev_used_by;
}	t_philo;

void		deallocate(pthread_mutex_t *forks,
				t_philo *p, int *held, int *prev);
void		init_forks(pthread_mutex_t *forks, int args);
void		destroy_forks(pthread_mutex_t *forks, int args);
int			ft_atoi(const char *nptr);
int			check_args(int argc, char *argv[], int args[5]);
int			init_pointers(pthread_mutex_t **forks,
				t_philo **p, int **held, int **prev);

#endif
