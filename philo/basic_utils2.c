/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:05:41 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/02 18:42:34 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(pthread_t *threads, t_philo *philosophers, int size)
{
	int				i;
	long long		b;

	b = get_time_now();
	i = 1;
	while (i < size)
	{
		philosophers[i].begin = b;
		pthread_create(&threads[i], NULL, philosopher,
			(void *)&philosophers[i]);
		//pthread_detach(threads[i]);
		i += 2;
	}
	i = 0;
	while (i < size - 1)
	{
		philosophers[i].begin = b;
		pthread_create(&threads[i], NULL, philosopher,
			(void *)&philosophers[i]);
		//pthread_detach(threads[i]);
		i += 2;
	}
	if (size % 2)
	{
		philosophers[size - 1].begin = b;
		pthread_create(&threads[size - 1], NULL, philosopher,
			(void *)&philosophers[size - 1]);
		//pthread_detach(threads[size - 1]);
	}
	return (1);
}

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
