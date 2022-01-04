/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_threads_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:59:20 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/04 19:28:58 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_first_fork(t_philo *data)
{
	pthread_mutex_unlock(data->death_checker_lock);
	pthread_mutex_lock(data->first_fork);
	pthread_mutex_lock(data->death_checker_lock);
	if (!*(data->alive))
	{
		pthread_mutex_unlock(data->first_fork);
		return (0);
	}
	printf("%8lld ms   P%d has taken the first fork\n",
		timestamp(data->begin), data->number);
	return (1);
}

int	lock_second_fork(t_philo *data)
{
	pthread_mutex_unlock(data->death_checker_lock);
	pthread_mutex_lock(data->second_fork);
	pthread_mutex_lock(data->death_checker_lock);
	data->last_meal = get_time_now();
	if (!*(data->alive))
	{
		pthread_mutex_unlock(data->first_fork);
		pthread_mutex_unlock(data->second_fork);
		return (0);
	}
	printf("%8lld ms   P%d has taken the second fork and is eating\n",
		timestamp(data->begin), data->number);
	return (1);
}

int	eat(t_philo *data)
{
	while (timestamp(data->last_meal) < data->teat)
	{
		pthread_mutex_unlock(data->death_checker_lock);
		usleep(1000);
		pthread_mutex_lock(data->death_checker_lock);
	}	
	pthread_mutex_unlock(data->first_fork);
	pthread_mutex_unlock(data->second_fork);
	data->meals--;
	if (!data->meals)
	{
		printf("%8lld ms   P%d finished the last meal\n",
			timestamp(data->begin), data->number);
		return (0);
	}
	return (1);
}

int	has_died(t_philo *data)
{
	if (!*(data->alive))
	{
		return (1);
	}
	return (0);
}

void	go_to_sleep(t_philo *data, long long marker)
{
	while (timestamp(marker) < data->tsleep)
	{
		pthread_mutex_unlock(data->death_checker_lock);
		usleep(1000);
		pthread_mutex_lock(data->death_checker_lock);
	}
}
