/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:05:41 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/07 11:17:14 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_args(t_philo *philosophers, int args[6], int i)
{
	philosophers->alive = &args[5];
	philosophers->total = args[0];
	philosophers->tdie = args[1];
	philosophers->teat = args[2];
	philosophers->tsleep = args[3];
	philosophers->meals = args[4];
	philosophers->number = i + 1;
}

void	init_philosophers(t_philo *philosophers,
	sem_t *forks, pid_t *pids, int args[6])
{
	int				i;
	long long		b;

	b = get_time_now();
	args[5] = 1;
	i = 0;
	while (i < args[0])
	{
		philosophers[i].begin = b;
		philosophers[i].last_meal = philosophers[i].begin;
		philosophers[i].pids = pids;
		philosophers[i].forks = forks;
		init_args(&philosophers[i], args, i);
		i++;
	}
}

void	fork_kids(pid_t *pids, t_philo *philosophers, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			exit(philo(philosophers, i));
		}
		i++;
	}
}

void	wait_kids(pid_t *pids, int size)
{
	int	i;
	int	r;

	i = 0;
	while (i < size)
	{
		waitpid(-1, &r, 0);
		if (WSTOPSIG(r) == 1)
		{
			terminate(pids, size);
			break ;
		}
		i++;
	}
}

void	terminate(pid_t *pids, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
}
