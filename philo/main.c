/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:34:03 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/01 11:30:37 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *philo_data)
{
	t_philo	*data;
	int		*alive;

	data = (t_philo *)(philo_data);
	*alive = data->alive; 
	while (*alive)
	{
		printf("philosopher %d\n", data->number);
		usleep(10000);
	}
	return (NULL);
}

void	*status_updates(void *tid)
{
	return (tid);
}

void	init_philosophers(t_philo *p, pthread_mutex_t *forks, int args[6])
{
	int	i;

	i = 0;
	args[5] = 1;
	while (i < args[0])
	{
		p[i].alive = &args[5];
		p[i].total = args[0];
		p[i].number = i + 1;
		if (i == args[0] - 1)
		{
			p[i].first_fork = &forks[0];
			p[i].second_fork = &forks[args[0] - 1];
		}
		else
		{
			p[i].first_fork = &forks[i];
			p[i].second_fork = &forks[i + 1];
		}
		p[i].change = false;
		i++;
	}
}

int	start_threads(pthread_t *threads, t_philo *philosophers)
{
}

//args[0] number of philosophers
//args[1] time_to_die
//args[2] time_to_eat
//arg[3] time_to_sleep
//arg[4] number_of_times_each_philosopher_must_eat
int	main(int argc, char *argv[])
{
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	t_philo			*philosophers;
	int				args[6];

	if (!check_args(argc, argv, args))
		return (write(1, "Problem with arguments!\n", 25));
	if (!aloc_pointers(&forks, &philosophers, &threads, args[0]))
		return (write(1, "Problem with memory allocation!\n", 33));
	init_forks(forks, args[0]);
	init_philosophers(philosophers, forks, args);
	start_threads(threads, philosophers);
	destroy_forks(forks, args[0]);
	deallocate(forks, philosophers, threads);
	pthread_exit(NULL);
	return (0);
}
