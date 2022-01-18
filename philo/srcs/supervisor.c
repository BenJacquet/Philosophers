/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:25:20 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/18 14:36:01 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	stop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		pthread_mutex_lock(&data->philo[i].active);
		data->philo[i].stopped = 1;
		pthread_mutex_unlock(&data->philo[i].active);
		i++;
	}
}

void	end(t_data *data)
{
	int	i;
	int	died;

	i = 0;
	died = 0;
	while (1)
	{
		i = 0;
		died = 0;
		while (i < data->nb)
		{
			pthread_mutex_lock(&data->philo[i].active);
			if (data->philo[i].ended == 1 || data->nb == 1)
				died++;
			pthread_mutex_unlock(&data->philo[i].active);
			i++;
			if (died == data->nb)
				return ;
		}
	}
}

int	check_starvation(t_data *data, int i)
{
	pthread_mutex_lock(&data->philo[i].active);
	if (timestamp(data->philo[i].last_meal) >= (unsigned long)data->philo[i].die
		|| data->philo[i].stopped == 1)
	{
		pthread_mutex_unlock(&data->philo[i].active);
		stop(data);
		printf("%lums %d died\n", timestamp(data->philo[i].start) \
			, data->philo[i].id);
		end(data);
		return (1);
	}
	pthread_mutex_unlock(&data->philo[i].active);
	return (0);
}

int	check_fullness(t_data *data)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < data->nb)
	{
		pthread_mutex_lock(&data->philo[i].active);
		if (data->philo[i].meals == data->philo[i].max_meals
			&& data->philo[i].max_meals != -1)
			full++;
		pthread_mutex_unlock(&data->philo[i].active);
		i++;
	}
	if (full == data->nb)
	{
		stop(data);
		end(data);
		return (1);
	}
	return (0);
}

void	*supervisor(void *v_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)v_data;
	while (1)
	{
		i = 0;
		while (i < data->nb)
		{
			if (check_fullness(data) == 1)
				return (NULL);
			if (check_starvation(data, i))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
