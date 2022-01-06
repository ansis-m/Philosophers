/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:34:03 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/06 19:08:22 by amalecki         ###   ########.fr       */
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
 //runs forever, dies with the child, memory is not an issue
void	*death_checker(void *philo_data)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)philo_data;
	i = 0;
	while (i < 20)// / p->number)
	{
		printf("hello from the death_checker %d\n", p->number);
		sleep(2);
		// if (still_alive(p) && *(p->alive))
		// {
		// 	usleep(1000);
		// }
		// else
		// {
		// 	if (*(p->alive) && p->meals)
		// 	{
		// 		printf("%8lld ms   P%d died :(\n",
		// 			timestamp(p->begin), p->number);
		// 		*(p->alive) = 0;
		// 	}
		// 	break ;
		// }
		i++;
	}
	return (NULL);
}

void	philo(t_philo	*philosophers, int i)
{
	pthread_t	d_checker;

	pthread_create(&d_checker, NULL, death_checker, (void *)(philosophers +i));
	pthread_detach(d_checker);
	printf("philosopher %d\n", i + 1);
	for (int j = 0; j < philosophers[i].number; j++)
		sleep(2);
	printf("exiting child %d thread detached\n", philosophers[i].number);
	deallocate(philosophers, philosophers[i].pids);
	if (true)
		exit(22);
	exit(22);
}

int	main(int argc, char *argv[])
{
	t_philo			*philosophers;
	pid_t			*pids;
	int				args[6];

	if (check_args(argc, argv, args) != 1)
		return (write(1, "Problem with arguments!\n", 25));
	if (!aloc_pointers(&philosophers, &pids, args[0]))
		return (write(1, "Problem with memory allocation!\n", 33));
	init_philosophers(philosophers, pids, args);
	fork_kids(pids, philosophers, args[0]);
	wait_kids(pids, args[0]);
	usleep(200000);
	deallocate(philosophers, pids);
	return (0);
}
