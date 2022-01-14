/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:24:20 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/14 15:27:45 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	end_philo(t_philo *philo, int code)
{
	if (code == 1)
		pthread_mutex_unlock(philo->first);
	else if (code == 2 || code == 3)
	{
		pthread_mutex_unlock(philo->first);
		pthread_mutex_unlock(philo->second);
	}
}

void	print_action(const char *action, t_philo *philo, int code)
{
	pthread_mutex_lock(&philo->active);
	pthread_mutex_lock(&philo->alive);
	if (code == 3)
	{
		gettimeofday(&philo->last_meal, NULL);
		philo->meals++;
	}
	if (philo->stopped == 0)
		printf(action, timestamp(philo->start), philo->id);
	pthread_mutex_unlock(&philo->alive);
	pthread_mutex_unlock(&philo->active);
	if (code == 3)
		usleep(philo->eat * 1000);
	else if (code == 4)
		usleep(philo->sleep * 1000);
}

int	action(t_philo *philo, int code)
{
	pthread_mutex_lock(&philo->alive);
	if (philo->stopped == 1)
	{
		pthread_mutex_unlock(&philo->alive);
		end_philo(philo, code);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->alive);
		if (code == 1 || code == 2)
			print_action("%lums %d has taken a fork\n", philo, code);
		if (philo->nb == 1)
		{
			pthread_mutex_unlock(philo->first);
			return (1);
		}
		else if (code == 3)
			print_action("%lums %d is eating\n", philo, code);
		else if (code == 4)
			print_action("%lums %d is sleeping\n", philo, code);
		else
			print_action("%lums %d is thinking\n", philo, code);
		return (0);
	}
}

int	routine(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->first);
		if (action(philo, 1) == 1)
			return (1);
		pthread_mutex_lock(philo->second);
		if (action(philo, 2) == 1)
			return (1);
		if (action(philo, 3) == 1)
			return (1);
		pthread_mutex_unlock(philo->first);
		pthread_mutex_unlock(philo->second);
		pthread_mutex_lock(&philo->alive);
		if ((philo->meals == philo->max_meals && philo->max_meals != -1)
			|| philo->stopped == 1)
		{
			pthread_mutex_unlock(&philo->alive);
			return (1);
		}
		pthread_mutex_unlock(&philo->alive);
		if (action(philo, 4) == 1)
			return (1);
		if (action(philo, 5) == 1)
			return (1);
	}
}

void	*wrapper(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	routine(philo);
	pthread_mutex_lock(&philo->alive);
	philo->ended = 1;
	pthread_mutex_unlock(&philo->alive);
	return (NULL);
}
