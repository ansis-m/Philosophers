/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 12:43:31 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/05 17:08:07 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(int argc, char *argv[], int args[5])
{
	int	i;
	int	j;	

	if (argc != 5 && argc != 6)
		return (0);
	args[4] = -999;
	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		args[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	if (args[0] == 0 || args[0] > 200 || args[2] < 10 || args[3] < 10)
		return (0);
	return (1);
}

int	aloc_pointers(t_philo **philosophers, int size)
{
	*philosophers = (t_philo *)malloc(sizeof(t_philo) * size);
	if (!*philosophers)
	{
		deallocate(*philosophers);
		return (0);
	}
	return (1);
}

void	deallocate(t_philo *philosophers)
{
	free(philosophers);
}
