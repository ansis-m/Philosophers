/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 19:26:08 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/03 14:21:28 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//timestamp_in_ms X is sleeping
void	*philosopher(void *philo_data)
{
	t_philo			*data;
	int				*live;
	long long	marker;

	data = (t_philo *)(philo_data);
	live = data->alive;
	data->last_meal = data->begin;
	if (! (data->number % 2))
	{
		printf("timestamp: %lld\t philosopher %d is thinking\n", timestamp(data->begin), data->number);
		usleep(data->teat * 1000);
	}
	if (data->total % 2 && data->total > 1 && data->number == data->total)
	{
		printf("timestamp: %lld\t philosopher %d is thinking\n", timestamp(data->begin), data->number);
		usleep(data->teat * 2000);
	}
	if (data->total == 1)
	{
		printf("timestamp: %lld\t philosopher %d has taken the first fork\n", timestamp(data->begin), data->number);
		return (NULL);
	}
	while (*live && data->meals)
	{
		pthread_mutex_lock(data->first_fork);
		if (!*live)
		{
			pthread_mutex_unlock(data->first_fork);
			return (NULL);
		}
		printf("timestamp: %lld\t philosopher %d has taken the first fork\n", timestamp(data->begin), data->number);
		pthread_mutex_lock(data->second_fork);
		data->last_meal = get_time_now();
		if (!*live)
		{
			pthread_mutex_unlock(data->first_fork);
			pthread_mutex_unlock(data->second_fork);
			return (NULL);
		}
		printf("timestamp: %lld\t philosopher %d has taken the second fork and is eating\n", timestamp(data->begin), data->number);
		while (timestamp(data->last_meal) < data->teat)
		{
			usleep(1000);
		}	
		pthread_mutex_unlock(data->first_fork);
		pthread_mutex_unlock(data->second_fork);
		marker = get_time_now();
		if (!*live)
			return (NULL);
		printf("timestamp: %lld\t philosopher %d is sleeping\n", timestamp(data->begin), data->number);
		while (timestamp(marker) < data->tsleep)
		{
			usleep(1000);
		}
		data->meals--;
		if (!*live)
			return (NULL);
		printf("timestamp: %lld\t philosopher %d is thinking\n", timestamp(data->begin), data->number);
		if (data->total % 2 && 2 * data->teat > data->tsleep)
		{
			usleep((2 * data->teat - data->tsleep) * 1000);
		}
	}
	return (NULL);
}

int	start_threads(pthread_t *threads, t_philo *philosophers, int size)
{
	int				i;
	long long		b;

	b = get_time_now();
	i = 0;
	while (i < size)
	{
		philosophers[i].begin = b;
		pthread_create(&threads[i], NULL, philosopher,
			(void *)&philosophers[i]);
		i++ ;
	}
	return (1);
}
