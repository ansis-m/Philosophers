/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 19:26:08 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/03 11:03:12 by amalecki         ###   ########.fr       */
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
			return (NULL);
		printf("timestamp: %lld\t philosopher %d has taken the first fork\n", timestamp(data->begin), data->number);
		pthread_mutex_lock(data->second_fork);
		data->last_meal = get_time_now();
		marker = data->last_meal;
		if (!*live)
			return (NULL);
		printf("timestamp: %lld\t philosopher %d has taken the second fork and is eating\n", timestamp(data->begin), data->number);
		while (timestamp(marker) < data->teat)
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
	}
}

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
		i += 2;
	}
	i = 0;
	while (i < size - 1)
	{
		philosophers[i].begin = b;
		pthread_create(&threads[i], NULL, philosopher,
			(void *)&philosophers[i]);
		i += 2;
	}
	if (size % 2)
	{
		philosophers[size - 1].begin = b;
		pthread_create(&threads[size - 1], NULL, philosopher,
			(void *)&philosophers[size - 1]);
	}
	return (1);
}
