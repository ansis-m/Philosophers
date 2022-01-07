/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 12:43:31 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/07 08:45:33 by amalecki         ###   ########.fr       */
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
	if (!args[4])
		return (printf("There is no food! The bowl is empty!\n"));
	return (1);
}

int	aloc_pointers(t_philo **philosophers, pid_t	**pids, int size)
{
	int	i;

	*philosophers = (t_philo *)malloc(sizeof(t_philo) * size);
	*pids = (pid_t *)malloc(sizeof(pid_t) * (size + 1));
	if (!*philosophers || !*pids)
	{
		deallocate(*philosophers, *pids);
		return (0);
	}
	i = 0;
	while (i < size)
	{
		*(*pids + i) = 999;
		i++;
	}
	return (1);
}

void	deallocate(t_philo *philosophers, pid_t	*pids)
{
	free(philosophers);
	free(pids);
}

long long	get_time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	timestamp(long long begin)
{
	return (get_time_now() - begin);
}
