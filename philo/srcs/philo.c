/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:54:36 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/17 13:51:30 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

// void	print_text(const char *action, t_philo *philo)
// {
// 	unsigned long	time;

// 	time = timestamp(philo->start);
// 	pthread_mutex_lock(philo->active);
// 	printf();
// 	pthread_mutex_unlock(philo->active);
// }

void	launch_philos(t_data *data)
{
	int			i;
	pthread_t	reaper;

	i = 0;
	while (i < data->nb)
	{
		pthread_create(&data->philo[i].thread, NULL, wrapper, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->nb)
	{
		pthread_detach(data->philo[i++].thread);
		usleep(10);
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
