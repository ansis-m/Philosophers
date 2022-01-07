/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:39:36 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/07 11:41:10 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eat(t_philo *data)
{
	while (timestamp(data->last_meal) < data->teat && *(data->alive))
	{
		usleep(1000);
	}	
	sem_post(data->forks);
	sem_post(data->forks);
	data->meals--;
	return (1);
}

void	go_to_sleep(t_philo *data, long long marker)
{
	while (timestamp(marker) < data->tsleep && *(data->alive))
	{
		usleep(1000);
	}
}
