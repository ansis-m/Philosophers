/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:05:41 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/06 19:31:28 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

long long	get_time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	timestamp(long long begin)
{
	return (get_time_now() - begin);
}
