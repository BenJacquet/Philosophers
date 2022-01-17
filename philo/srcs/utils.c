/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:21:34 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/17 17:48:54 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	size_t	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - 48);
	return (result * sign);
}

unsigned long	timestamp(struct timeval start)
{
	struct timeval	current;
	unsigned long	stamp;

	gettimeofday(&current, NULL);
	stamp = ((current.tv_sec * 1000) + (current.tv_usec / 1000))
		- ((start.tv_sec * 1000) + (start.tv_usec / 1000));
	return (stamp);
}

unsigned long	gettime(void)
{
	struct timeval	current;
	unsigned long	time;

	gettimeofday(&current, NULL);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (time);
}

void	ft_mssleep(unsigned long temps_ms)
{
	struct timeval	time_towait;

	gettimeofday(&time_towait, NULL);
	while (timestamp(time_towait) < temps_ms)
		usleep(100);
}
