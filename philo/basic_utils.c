/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 12:43:31 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/31 19:14:51 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (1);
}

int	aloc_pointers(pthread_mutex_t **forks, t_philo **p, int **held, int **prev)
{
	int	size;

	size = **held;
	*forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
	*p = (t_philo *)malloc(sizeof(t_philo) * size);
	*held = (int *)malloc(sizeof(int) * size);
	*prev = (int *)malloc(sizeof(int) * size);
	if (!*forks || !*p || !*held || !*prev)
	{
		deallocate(*forks, *p, *held, *prev);
		return (0);
	}
	return (1);
}

void	deallocate(pthread_mutex_t *forks, t_philo *p, int *held, int *prev)
{
	free(held);
	free(prev);
	free(forks);
	free(p);
}

void	init_forks(pthread_mutex_t *forks, int args)
{
	int	i;

	i = 0;
	while (i < args)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	destroy_forks(pthread_mutex_t *forks, int args)
{
	int	i;

	i = 0;
	while (i < args)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
