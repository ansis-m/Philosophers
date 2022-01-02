/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker_threads.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:41:22 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/02 19:09:56 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_checker(void *philo_data)
{
	t_philo	*checker;

	checker = (t_philo *)philo_data;
	while (checker->meals)
		usleep(1000);
	return (NULL);
}

int	start_death_checker_threads(pthread_t *threads, t_philo *philosophers, int size)
{
	int				i;

	i = 0;
	while (i < size)
	{
		pthread_create(&threads[size + i], NULL, death_checker,
			(void *)&philosophers[i]);
		//pthread_detach(threads[i]);
		i ++;
	}
	return (1);
}
