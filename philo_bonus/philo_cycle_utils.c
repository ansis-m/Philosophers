/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 09:03:29 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/07 11:37:44 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	delay(t_philo *data, int multiplier)
{
	printf("%8lld ms   P%d is thinking\n", timestamp(data->begin), data->number);
	usleep(data->teat * multiplier);
}

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
		return (1);
	}
	return (1);
}

bool	still_alive(t_philo *philosopher)
{
	if (get_time_now() < philosopher->last_meal + philosopher->tdie)
		return (true);
	return (false);
}

int	lock_first_fork(t_philo *data)
{
	sem_wait(data->forks);
	if (!*(data->alive))
	{
		sem_post(data->forks);
		return (0);
	}
	printf("%8lld ms   P%d has taken the first fork\n",
		timestamp(data->begin), data->number);
	return (1);
}

int	lock_second_fork(t_philo *data)
{
	sem_wait(data->forks);
	data->last_meal = get_time_now();
	if (!*(data->alive))
	{
		sem_post(data->forks);
		sem_post(data->forks);
		return (0);
	}
	printf("%8lld ms   P%d has taken the second fork and is eating\n",
		timestamp(data->begin), data->number);
	return (1);
}
