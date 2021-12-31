/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:27:15 by ansis             #+#    #+#             */
/*   Updated: 2021/12/31 12:35:15 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	calculate(int sign, const char *nptr)
{
	long long int	result;
	int				i;

	i = 0;
	result = 0;
	while (true)
	{
		if (result > 2147483647 && sign == 1)
			return (-1);
		if (result > 2147483648 && sign == -1)
			return (0);
		if (*(nptr + i) < '0' || *(nptr + i) > '9')
			return ((int)(result * sign));
		result = result * 10 + *(nptr + i) - '0';
		i++;
	}
}

int	ft_atoi(const char *nptr)
{
	int				sign;
	int				i;

	if (!nptr)
		return (0);
	i = 0;
	sign = 1;
	while (*(nptr + i) == ' ' || *(nptr + i) == '\n' || *(nptr + i) == '\v'
		|| *(nptr + i) == '\t' || *(nptr + i) == '\f' || *(nptr + i) == '\r')
		i++;
	if (*(nptr + i) == '+' || *(nptr + i) == '-')
	{
		if (*(nptr + i) == '-')
			sign = -1;
		i++;
	}
	return (calculate(sign, nptr + i));
}
