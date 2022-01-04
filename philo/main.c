/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:34:03 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/04 14:48:00 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_args(t_philo *p, int args[6], int i)
{
	p->alive = &args[5];
	p->total = args[0];
	p->tdie = args[1];
	p->teat = args[2];
	p->tsleep = args[3];
	p->meals = args[4];
	p->number = i + 1;
}

static void	init_philosophers(t_philo *p, pthread_mutex_t *forks,
	pthread_mutex_t *death_checker_locks, int args[6])
{
	int				i;

	args[5] = 1;
	i = 0;
	while (i < args[0])
	{
		init_args(&p[i], args, i);
		if (i == args[0] - 1)
		{
			p[i].first_fork = forks;
			p[i].second_fork = forks + args[0] - 1;
		}
		else
		{
			p[i].first_fork = forks + i;
			p[i].second_fork = forks + i + 1;
		}
		p[i].death_checker_lock = death_checker_locks + i;
		p[i].indicator_lock = death_checker_locks + args[0];
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
	pthread_mutex_t	*death_checker_locks;
	pthread_t		*threads;
	t_philo			*philosophers;
	int				args[6];

	if (!check_args(argc, argv, args))
		return (write(1, "Problem with arguments!\n", 25));
	if (!aloc_pointers(&forks, &philosophers, &threads, args[0]))
		return (write(1, "Problem with memory allocation!\n", 33));
	init_forks(forks, args[0]);
	if (init_death_checker_locks(&death_checker_locks, args[0]) && args[4])
	{
		init_philosophers(philosophers, forks, death_checker_locks, args);
		start_threads(threads, philosophers, args[0]);
		start_death_checker_threads(threads, philosophers, args[0]);
		join_threads(threads, args[0]);
		destroy_forks(death_checker_locks, args[0]);
	}
	if (!args[4])
		printf("There is no food! The bowl is empty!\n");
	destroy_forks(forks, args[0]);
	deallocate(forks, death_checker_locks, philosophers, threads);
	return (0);
}
