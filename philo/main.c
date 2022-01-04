/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:34:03 by amalecki          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2022/01/03 15:35:57 by amalecki         ###   ########.fr       */
=======
/*   Updated: 2022/01/04 10:32:13 by amalecki         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philosophers(t_philo *p, pthread_mutex_t *forks,
	pthread_mutex_t *death_checker_locks, int args[6])
{
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
		//printf("number %d and death_lock: %p\n", p[i].number, p[i].death_checker_lock);
		i++;
	}
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
		//start_death_checker_threads(threads, philosophers, args[0]);
		join_threads(threads, args[0]);
		destroy_forks(death_checker_locks, args[0]);
	}
	if (!args[4])
		printf("There is no food! The bowl is empty!\n");
	destroy_forks(forks, args[0]);
	deallocate(forks, death_checker_locks, philosophers, threads);
	return (0);
}
