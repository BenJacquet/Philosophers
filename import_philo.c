/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:08:01 by jabenjam          #+#    #+#             */
/*   Updated: 2021/07/23 11:58:49 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// AJOUTER EXIT SI PHILOSOPHE SOLO

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;
	char	*str;

	if (!s1)
		return (NULL);
	str = (char*)s1;
	i = 0;
	while (str[i] != '\0')
		i++;
	if ((dup = malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	init_forks(t_params *params)
{
	int		i;

	i = 0;
	if (!(params->forks = malloc(sizeof(pthread_mutex_t) * params->nb)))
		return ;
	while (i < params->nb)
		pthread_mutex_init(&params->forks[i++], NULL);
}

void	init_philo(t_philo *philo_data, t_params *params, int id)
{
	philo_data->id = id;
	params.philo_data[id]->last_meal = 0;
	params.philo_data[id]->meals = 0;
	if (id % 2)
	{
		philo_data->first = &params->forks[id];
		philo_data->second = &params->forks[(id + 1) % params->nb];
	}
	else
	{
		philo_data->first = &params->forks[(id + 1) % params->nb];
		philo_data->second = &params->forks[id];
	}
}

void	init_params(int ac, char **av, t_params *params)
{
	params->nb = atoi(av[1]);
	params->die = (atoi(av[2]) * 1000);
	params->eat = (atoi(av[3]) * 1000);
	params->sleep = (atoi(av[4]) * 1000);
	params->max_meals = -1;
	if (ac == 6)
		params->max_meals = atoi(av[5]);
	init_forks(params);
}

void	routine()
{}

int		philosophers(int ac, char **av)
{
	t_params		params;
	t_philo			*philo_data;
	pthread_t		*philosophers;
	int				i;

	i = 0;
	init_params(ac, av, &params);
	philo_data = malloc(sizeof(t_philo) * (params.nb + 1));
	while (i < params.nb)
	{
		init_philo(&philo_data[i], &params, i);
		i++;
	}
	i = 0;
	philosophers = malloc(sizeof(pthread_t) * (params.nb + 1));
	while (i < params.nb)
	{
		pthread_create(&philosophers[i], NULL, &routine, (void*)&philo_data[i]);
		i++;
	}
	i = 0;
	while (i < params.nb)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
}

int		main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		philosophers(ac, av);
	}
	else
		return (1);
	return (0);
}
