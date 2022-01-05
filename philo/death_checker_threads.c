/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker_threads.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:41:22 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/05 11:49:25 by amalecki         ###   ########.fr       */
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
	t_philo	*p;

	p = (t_philo *)philo_data;
	pthread_mutex_lock(p->death_checker_lock);
	//pthread_mutex_lock(p->indicator_lock);
	while (1)
	{
		if (still_alive(p) && *(p->alive))
		{
			//pthread_mutex_unlock(p->indicator_lock);
			pthread_mutex_unlock(p->death_checker_lock);
			usleep(1000);
			pthread_mutex_lock(p->death_checker_lock);
			//pthread_mutex_lock(p->indicator_lock);
		}
		else
		{
			if (*(p->alive) && p->meals)
			{
				printf("%8lld ms   P%d died :(\n", timestamp(p->begin), p->number);
				*(p->alive) = 0;
			}
			break ;
		}
	}
	//pthread_mutex_unlock(p->indicator_lock);
	pthread_mutex_unlock(p->death_checker_lock);
	return (NULL);
}

int	start_death_checker_threads(pthread_t *threads,
	t_philo *philosophers, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_create(&threads[size + i], NULL, death_checker,
			(void *)&philosophers[i]);
		i ++;
	}
	return (1);
}

int	init_death_checker_locks(pthread_mutex_t **death_checker_locks, int size)
{
	int	i;

	*death_checker_locks
		= (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size + 1);
	if (!*death_checker_locks)
		return (0);
	i = 0;
	while (i < size)
	{
		pthread_mutex_init(*death_checker_locks + i, NULL);
		i++;
	}
	return (1);
}
