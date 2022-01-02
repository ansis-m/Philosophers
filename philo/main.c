/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:34:03 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/02 19:14:50 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//timestamp_in_ms X is sleeping
void	*philosopher(void *philo_data)
{
	t_philo			*data;
	int				*live;
	long long	marker;

	data = (t_philo *)(philo_data);
	live = data->alive;
	data->last_meal = data->begin;
	if (! (data->number % 2))
	{
		printf("timestamp: %lld\t philosopher %d is thinking\n", timestamp(data->begin), data->number);
		usleep(data->teat * 1000 / 2);
	}
	if (data->total % 2 && data->total > 1 && data->number == data->total)
	{
		printf("timestamp: %lld\t philosopher %d is thinking\n", timestamp(data->begin), data->number);
		usleep(data->teat * 1000 + 1000);
	}
	while (*live && data->meals)
	{
		pthread_mutex_lock(data->first_fork);
		printf("timestamp: %lld\t philosopher %d has taken the first fork\n", timestamp(data->begin), data->number);
		pthread_mutex_lock(data->second_fork);
		data->last_meal = get_time_now();
		marker = data->last_meal;
		if (!*live)
			break;
		printf("timestamp: %lld\t philosopher %d has taken the second fork and is eating\n", timestamp(data->begin), data->number);
		while (timestamp(marker) < data->teat)
		{
			usleep(1000);
		}	
		pthread_mutex_unlock(data->first_fork);
		pthread_mutex_unlock(data->second_fork);
		marker = get_time_now();
		if (!*live)
			break;
		printf("timestamp: %lld\t philosopher %d is sleeping\n", timestamp(data->begin), data->number);
		while (timestamp(marker) < data->tsleep)
		{
			usleep(1000);
		}
		data->meals--;
		if (!*live)
			break;
		printf("timestamp: %lld\t philosopher %d is thinking\n", timestamp(data->begin), data->number);
	}
	return (NULL);
}

void	init_philosophers(t_philo *p, pthread_mutex_t *forks, int args[6])
{
	struct timeval	begin;
	int				i;

	args[5] = 1;
	i = 0;
	while (i < args[0])
	{
		p[i].alive = &args[5];
		p[i].total = args[0];
		p[i].tdie = args[1];
		p[i].teat = args[2];
		p[i].tsleep = args[3];
		p[i].meals = args[4];
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
		i++;
	}
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
	start_threads(threads, philosophers, args[0]);
	start_death_checker_threads(threads, philosophers, args[0]);
	join_threads(threads, args[0]);
	destroy_forks(forks, args[0]);
	deallocate(forks, philosophers, threads);
	pthread_exit(NULL);
	return (0);
}
