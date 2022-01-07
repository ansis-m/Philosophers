/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 09:03:29 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/07 11:25:50 by amalecki         ###   ########.fr       */
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
