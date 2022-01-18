/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:01:40 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/18 13:32:08 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	initialization_two(t_data *data, struct timeval start)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		data->philo[i].first = &data->forks[i];
		data->philo[i].second = &data->forks[(i + 1) % data->nb];
		pthread_mutex_init(&data->philo[i].active, NULL);
		data->philo[i].start = start;
		gettimeofday(&data->philo[i++].last_meal, NULL);
	}
}

void	initialization(t_data *data, struct timeval start)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->nb));
	if (data->forks == NULL)
	{
		free(data->philo);
		return ;
	}
	while (i < data->nb)
		pthread_mutex_init(&data->forks[i++], NULL);
	initialization_two(data, start);
}
