/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 19:26:08 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/04 19:26:50 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initial_delay(t_philo *data)
{
	if (! (data->number % 2))
		delay(data, 1000);
	if (data->total % 2 && data->total > 1 && data->number == data->total)
		delay(data, 2000);
	if (data->total == 1)
	{
		printf("%8lld ms   P%d has taken the first fork\n",
			timestamp(data->begin), data->number);
		pthread_mutex_unlock(data->death_checker_lock);
		return (0);
	}
	return (1);
}

void	delay(t_philo *data, int multiplier)
{
	printf("%8lld ms   P%d is thinking\n", timestamp(data->begin), data->number);
	pthread_mutex_unlock(data->death_checker_lock);
	usleep(data->teat * multiplier);
	pthread_mutex_lock(data->death_checker_lock);
}

int	philo_cycle(t_philo *data, long long sleep) //dont touch the mutexes upon exit
{
	long long	marker;

	while (true)
	{
		if (!lock_first_fork(data) || !lock_second_fork(data))
			return (0);
		if (!eat(data))
			return (0);
		if (has_died(data))
			return (0);
		marker = get_time_now();
		printf("%8lld ms   P%d is sleeping\n", timestamp(data->begin), data->number);
		go_to_sleep(data, marker);
		if (has_died(data))
			return (0);
		printf("%8lld ms   P%d is thinking\n", timestamp(data->begin), data->number);
		if (data->total % 2 && sleep > 0)
		{
			pthread_mutex_unlock(data->death_checker_lock);
			usleep(sleep);
			pthread_mutex_lock(data->death_checker_lock);
		}	
	}
	return (1);
}

void	*philosopher(void *philo_data)
{
	long long	sleep;
	t_philo		*data;

	data = (t_philo *)(philo_data);
	pthread_mutex_lock(data->death_checker_lock);
	data->last_meal = data->begin;
	sleep = (2 * data->teat - data->tsleep) * 1000;
	if (! initial_delay(data))
		return (NULL);
	philo_cycle(data, sleep);
	pthread_mutex_unlock(data->death_checker_lock);
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
