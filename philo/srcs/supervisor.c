/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:25:20 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/14 11:38:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	stop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		pthread_mutex_lock(&data->philo[i].alive);
		data->philo[i].stopped = 1;
		pthread_mutex_unlock(&data->philo[i].alive);
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
			pthread_mutex_lock(&data->philo[i].alive);
			if (data->philo[i].ended == 1 || data->nb == 1)
				died++;
			pthread_mutex_unlock(&data->philo[i].alive);
			i++;
			if (died == data->nb)
				return ;
		}
	}
}

int	check_starvation(t_data *data, int i)
{
	if (timestamp(data->philo[i].last_meal) >= (unsigned long)data->philo[i].die
		|| data->philo[i].stopped == 1)
	{
		pthread_mutex_unlock(&data->philo[i].alive);
		stop(data);
		printf("%lums %d died\n", timestamp(data->philo[i].start) \
			, data->philo[i].id);
		pthread_mutex_unlock(&data->philo[i].active);
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
			pthread_mutex_lock(&data->philo[i].active);
			if (data->philo[i].meals == data->philo[i].max_meals
				&& data->philo[i].max_meals != -1)
			{
				pthread_mutex_unlock(&data->philo[i].active);
				return (NULL);
			}
			pthread_mutex_lock(&data->philo[i].alive);
			if (check_starvation(data, i))
				return (NULL);
			pthread_mutex_unlock(&data->philo[i].alive);
			pthread_mutex_unlock(&data->philo[i].active);
			i++;
		}
	}
	return (NULL);
}
