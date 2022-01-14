/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:54:36 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/14 12:09:33 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	initialization(t_data *data, struct timeval start)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->nb + 1));
	while (i < data->nb)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	while (i < data->nb)
	{
		if (i % 2)
		{
			data->philo[i].first = &data->forks[i];
			data->philo[i].second = &data->forks[(i + 1) % data->nb];
		}
		else
		{
			data->philo[i].first = &data->forks[(i + 1) % data->nb];
			data->philo[i].second = &data->forks[i];
		}
		pthread_mutex_init(&data->philo[i].active, NULL);
		pthread_mutex_init(&data->philo[i].alive, NULL);
		data->philo[i].start = start;
		gettimeofday(&data->philo[i].last_meal, NULL);
		i++;
	}
}

void	launch_philos(t_data *data)
{
	int			i;
	pthread_t	reaper;

	i = 0;
	while (i < data->nb)
	{
		pthread_create(&data->philo[i].thread, NULL, wrapper, &data->philo[i]);
		pthread_detach(data->philo[i++].thread);
	}
	pthread_create(&reaper, NULL, supervisor, data);
	pthread_join(reaper, NULL);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].active);
		pthread_mutex_destroy(&data->philo[i].alive);
		i++;
	}
	free(data->forks);
	free(data->philo);
	free(data);
}

int	core(int ac, char **av)
{
	t_data			*data;
	struct timeval	start;

	data = malloc(sizeof(t_data));
	gettimeofday(&start, NULL);
	if (parse_params(ac, av, data) == 1)
	{
		free(data);
		return (1);
	}
	initialization(data, start);
	launch_philos(data);
	cleanup(data);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
		return (core(ac, av));
	else
		return (1);
}
