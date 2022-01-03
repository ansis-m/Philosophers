/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker_threads.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:41:22 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/03 12:37:53 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	still_alive(t_philo *philosopher)
{
	if (get_time_now() < philosopher->last_meal + philosopher->tdie)
		return (true);
	return (false);
}

void	*death_checker(void *philo_data)
{
	t_philo	*checker;

	checker = (t_philo *)philo_data;
	while (*(checker->alive) && checker->meals)
	{
		if (still_alive(checker))
			usleep(1000);
		else
		{
			*(checker->alive) = 0;
			printf("timestamp: %lld\t philosopher %d has died :(\n", timestamp(checker->begin), checker->number);
		}
	}
	return (NULL);
}

int	start_death_checker_threads(pthread_t *threads,
	t_philo *philosophers, int size)
{
	int				i;

	i = 0;
	usleep(2000);
	while (i < size)
	{
		pthread_create(&threads[size + i], NULL, death_checker,
			(void *)&philosophers[i]);
		i ++;
	}
	return (1);
}
