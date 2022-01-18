/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:54:36 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/18 13:28:41 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	*wrapper(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	routine(philo);
	pthread_mutex_lock(&philo->active);
	philo->ended = 1;
	pthread_mutex_unlock(&philo->active);
	return (NULL);
}

void	launch_philos(t_data *data)
{
	int			i;
	pthread_t	reaper;

	i = 0;
	while (i < data->nb)
	{
		pthread_create(&data->philo[i].thread, NULL, wrapper, &data->philo[i]);
		usleep(500);
		i++;
	}
	i = 0;
	while (i < data->nb)
	{
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
		i++;
	}
	free(data->forks);
	free(data->philo);
}

int	core(int ac, char **av)
{
	t_data			data;
	struct timeval	start;

	gettimeofday(&start, NULL);
	if (parse_params(ac, av, &data) == 1)
		return (1);
	initialization(&data, start);
	launch_philos(&data);
	cleanup(&data);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
		return (core(ac, av));
	return (1);
}
