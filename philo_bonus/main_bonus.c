/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:34:03 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/05 19:47:27 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_args(t_philo *philosophers, int args[6], int i)
{
	philosophers->alive = &args[5];
	philosophers->total = args[0];
	philosophers->tdie = args[1];
	philosophers->teat = args[2];
	philosophers->tsleep = args[3];
	philosophers->meals = args[4];
	philosophers->number = i + 1;
}

static void	init_philosophers(t_philo *philosophers, pid_t	*pids, int args[6])
{
	int				i;

	args[5] = 1;
	i = 0;
	while (i < args[0])
	{
		philosophers[i].pids = pids;
		init_args(&philosophers[i], args, i);
		i++;
	}
}

void	philo(t_philo	*philosophers, int i)
{
	printf("philosopher %d\n", philosophers[i].number);
	for (int j =0; j < philosophers->total; j++)
		printf("philosophers%d, pid %d, j %d\n", philosophers[i].number, philosophers[i].pids[j], j);
	deallocate(philosophers, philosophers->pids);
}

//args[0] number of philosophers
//args[1] time_to_die
//args[2] time_to_eat
//arg[3] time_to_sleep
//arg[4] number_of_times_each_philosopher_must_eat
int	main(int argc, char *argv[])
{
	t_philo			*philosophers;
	pid_t			*pids;
	int				args[6];
	int				i;

	if (!check_args(argc, argv, args))
		return (write(1, "Problem with arguments!\n", 25));
	if (!aloc_pointers(&philosophers, &pids, args[0]))
		return (write(1, "Problem with memory allocation!\n", 33));
	init_philosophers(philosophers, pids, args);
	if (!args[4])
		printf("There is no food! The bowl is empty!\n");
	i = 0;
	while (i < args[0])
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			philo(philosophers, i);
			exit(0);
		}
		i++;
	}
	usleep(500000);
	for (int k = 0; k < args[0]; k++)
		printf("pids from main %d\n", pids[k]);
	printf("MAIN PID %d", getpid());
	deallocate(philosophers, pids);
	return (0);
}
