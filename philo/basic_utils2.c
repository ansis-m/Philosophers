/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:05:41 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/04 14:28:18 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(pthread_t *threads, int size)
{
	int	i;

	i = 0;
	while (i < 2 * size)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (1);
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
