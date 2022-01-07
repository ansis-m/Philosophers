/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:34:03 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/07 11:31:58 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	still_alive(t_philo *philosopher)
{
	if (get_time_now() < philosopher->last_meal + philosopher->tdie)
		return (true);
	return (false);
}

void	*death_checker(void *philo_data)
{
	t_philo	*p;

	p = (t_philo *)philo_data;
	while (true)
	{
		if (still_alive(p) && *(p->alive))
		{
			usleep(1000);
		}
		else
		{
			if (*(p->alive) && p->meals)
			{
				printf("%8lld ms   P%d died :(\n",
					timestamp(p->begin), p->number);
				*(p->alive) = 0;
			}
			break ;
		}
	}
	return (NULL);
}

int	lock_first_fork(t_philo *data)
{
	sem_wait(data->forks);
	if (!*(data->alive))
	{
		sem_post(data->forks);
		return (0);
	}
	printf("%8lld ms   P%d has taken the first fork\n",
		timestamp(data->begin), data->number);
	return (1);
}

int	lock_second_fork(t_philo *data)
{
	sem_wait(data->forks);
	data->last_meal = get_time_now();
	if (!*(data->alive))
	{
		sem_post(data->forks);
		sem_post(data->forks);
		return (0);
	}
	printf("%8lld ms   P%d has taken the second fork and is eating\n",
		timestamp(data->begin), data->number);
	return (1);
}

int	eat(t_philo *data)
{
	while (timestamp(data->last_meal) < data->teat && *(data->alive))
	{
		usleep(1000);
	}	
	sem_post(data->forks);
	sem_post(data->forks);
	data->meals--;
	return (1);
}

void	go_to_sleep(t_philo *data, long long marker)
{
	while (timestamp(marker) < data->tsleep && *(data->alive))
	{
		usleep(1000);
	}
}

int	philo_cycle(t_philo *data, long long sleep)
{
	while (data->meals)
	{
		if (data->total == 1)
		{
			usleep(1000);
			if (!*(data->alive))
				return (1);
			continue ;
		}
		if (!lock_first_fork(data) || !lock_second_fork(data))
			return (1);
		if (!eat(data))
			return (1);
		if (!*(data->alive))
			return (1);
		printf("%8lld ms   P%d is sleeping\n",
			timestamp(data->begin), data->number);
		go_to_sleep(data, get_time_now());
		if (!*(data->alive))
			return (1);
		printf("%8lld ms   P%d is thinking\n",
			timestamp(data->begin), data->number);
		if (sleep > 0 && data->total % 2)
		{
			usleep(sleep);
		}
	}
	return (22);
}

int	philo(t_philo	*philosophers, int i)
{
	pthread_t	d_checker;
	long long	sleep;
	int			status;

	pthread_create(&d_checker, NULL, death_checker, (void *)(philosophers + i));
	sleep = (philosophers[i].tdie - 2 * philosophers[i].teat
			- philosophers[i].tsleep) * 700;
	if (! initial_delay(philosophers + i))
		return (1);
	status = philo_cycle(philosophers + i, sleep);
	pthread_join(d_checker, NULL);
	sem_close(philosophers[i].forks);
	deallocate(philosophers, philosophers[i].pids);
	return (status);
}

int	main(int argc, char *argv[])
{
	t_philo			*philosophers;
	pid_t			*pids;
	sem_t			*forks;
	int				args[6];

	if (check_args(argc, argv, args) != 1)
		return (write(1, "Problem with arguments!\n", 25));
	if (!aloc_pointers(&philosophers, &pids, args[0]))
		return (write(1, "Problem with memory allocation!\n", 33));
	forks = sem_open("/forks", O_CREAT, S_IROTH | S_IWOTH, args[0]);
	init_philosophers(philosophers, forks, pids, args);
	fork_kids(pids, philosophers, args[0]);
	wait_kids(pids, args[0]);
	deallocate(philosophers, pids);
	sem_unlink("/forks");
	sem_close(forks);
	return (0);
}
