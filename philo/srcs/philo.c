/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:54:36 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/11 16:44:53 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

// === TO-DO ===

// Modifier les unites pour le last_meal

// === WORKFLOW ===

// 9 OK
// Prevention des deadlocks et datarace

// 8
// Liberation des ressources du thread (philosophe) apres sa routine
// Liberation des mutex (fourchettes)
// f = pthread_detach()

// 7b
// Sleep fait maison
// f = ft_sleep()

// 7a OK
// Routine des philos :
//  - Prendre une fourchette
//  - Prendre l'autre fourchette
//  - Manger
//  - Lacher la premiere fourchette
//  - Lacher la deuxieme fourchette
//  - Dormir
//  - Penser
//  - Arreter
// f = routine()

// 6 OK
// join des threads
// f = pthread_join()

// 5b OK
// Doit verifier le temps écoulé depuis le dernier repas sur chaque philosophe
// Si un philosophe meurt, doit detach tous les philosophes

// 5a OK
// Doit check si tous les philosophes ont atteint leur nombre de repas max

// 5 OK
// Creation du thread superviseur (reaper)
//  - Doit avoir les adresses de tous les philosophes
//  - Doit tuer les philosophes
//  - Doit tout clean apres max repas
//  - Doit tuer les philosophes si l' un d'eux meurt de faim
// f = pthread_create()
// r = *reaper

// 4 OK
// Creation et initialisation des threads (philosophes)
//  - Chacun doit avoir un pointeur vers ses fourchettes
// f = pthread_create()
// r = *philosophers

// 3 OK
// Creation et initialisation des mutex (fourchettes)
// - Tableau contenant toutes les fourchettes
// f = pthread_mutex_init()
// r = *forks

// 2 OK
// Gestion d'erreurs
//  - Aucun philosophe
//  - Valeur invalide
//  - Mauvais nombre d'arguments
// f = check_arguments()

// 1 OK
// Parsing des arguments : parse_arguments()
//  - Nombre de philosophes
//  - Temps pour mourir
//  - Temps pour manger
//  - Temps pour dormir
//  - Nombre de repas max (OPTIONNEL)
// f = parse_arguments()
// r = args[]

// ms = s * 1000 et us / 1000

unsigned long	timestamp(struct timeval time)
{
	struct timeval	current;
	unsigned long	stamp;

	gettimeofday(&current, NULL);
	stamp = ((current.tv_sec * 1000) + (current.tv_usec / 1000))
		- ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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

void	ft_mssleep(unsigned long ms)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	while (timestamp(current) < ms)
		usleep(100);
}

void	initialization(t_data *data, struct timeval start)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->nb));
	while (i < data->nb)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		printf("fork number %d address is %p\n", i, &data->forks[i]);
		i++;
	}
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
		printf("philosopher %d picks up %p first and %p second and life = %d\n", data->philo[i].id, data->philo[i].first, data->philo[i].second, data->philo[i].life);
		pthread_mutex_init(&data->philo[i].active, NULL);
		pthread_mutex_init(&data->philo[i].alive, NULL);
		data->philo[i].start = start;
		gettimeofday(&data->philo[i].last_meal, NULL);
		i++;
	}
	print_data(data);
}

int	action(t_philo *philo, int code)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(&philo->alive);
	if (philo->life == 1)
	{
		pthread_mutex_unlock(&philo->alive);
		if (code == 1)
		{
			pthread_mutex_lock(&philo->active);
			printf("%lums %d has taken a fork\n", timestamp(philo->start), philo->id);
			pthread_mutex_unlock(&philo->active);
		}
		else if (code == 2)
		{
			pthread_mutex_lock(&philo->active);
			gettimeofday(&philo->last_meal, NULL);
			printf("%lums %d is eating\n", timestamp(philo->start), philo->id);
			philo->meals++;
			pthread_mutex_unlock(&philo->active);
			ft_mssleep(philo->eat);
		}
		else if (code == 3)
		{
			pthread_mutex_lock(&philo->active);
			printf("%lums %d is sleeping\n", timestamp(philo->start), philo->id);
			pthread_mutex_unlock(&philo->active);
			ft_mssleep(philo->sleep);
		}
		else
		{
			pthread_mutex_lock(&philo->active);
			printf("%lums %d is thinking\n", timestamp(philo->start), philo->id);
			pthread_mutex_unlock(&philo->active);
		}
		ret = 0;
	}
	else
		pthread_mutex_unlock(&philo->alive);
	return (ret);
}

void	*routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo*)v_philo;
	while (1)
	{
		pthread_mutex_lock(philo->first);
		if (action(philo, 1) == 1)
		{
			pthread_mutex_unlock(philo->first);
			break ;
		}
		pthread_mutex_lock(philo->second);
		if (action(philo, 1) == 1)
		{
			pthread_mutex_unlock(philo->first);
			pthread_mutex_unlock(philo->second);
			break ;
		}
		if (action(philo, 2) == 1)
			break ;
		pthread_mutex_unlock(philo->first);
		pthread_mutex_unlock(philo->second);
		pthread_mutex_lock(&philo->alive);
		if ((philo->meals == philo->max_meals && philo->max_meals != -1) || philo->life == 0)
		{
			pthread_mutex_unlock(&philo->alive);
			break ;
		}
		pthread_mutex_unlock(&philo->alive);
		if (action(philo, 3) == 1)
			break ;
		if (action(philo, 4) == 1)
			break ;
	}
	return ((void*)0);
}

void	death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		pthread_mutex_lock(&data->philo[i].alive);
		data->philo[i].life = 0;
		pthread_mutex_unlock(&data->philo[i].alive);
		i++;
	}
}

void	*supervisor(void *v_data)
{
	t_data *data;
	int	i;

	data = (t_data*)v_data;
	while (1)
	{
		i = 0;
		while (i < data->nb)
		{
			pthread_mutex_lock(&data->philo[i].active);
			if (data->philo[i].meals == data->philo[i].max_meals && data->philo[i].max_meals != -1)
			{
				pthread_mutex_unlock(&data->philo[i].active);
				return (NULL);
			}
			if (timestamp(data->philo[i].last_meal) >= (unsigned long)data->philo[i].die)
			{
				// printf("timestamp_last_meal=%ld timestamp_start=%ld\n", timestamp(data->philo[i].last_meal), timestamp(data->philo[i].start));
				death(data);
				printf("%lums %d has died\n", timestamp(data->philo[i].start), data->philo[i].id);
				pthread_mutex_unlock(&data->philo[i].active);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].active);
			i++;
		}
	}
	return (NULL);
}

void	launch_philos(t_data *data)
{
	int	i;
	pthread_t	reaper;

	i = 0;
	while (i < data->nb)
	{
		pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]);
		pthread_detach(data->philo[i++].thread);
	}
	pthread_create(&reaper, NULL, supervisor, data);
	pthread_join(reaper, NULL);
}

int	core(int ac, char **av)
{
	t_data			*data;
	struct timeval	start;

	data = malloc(sizeof(t_data));
	gettimeofday(&start, NULL);
	if (parse_params(ac, av, data) == 1)
	{
		// free(data);
		return (1);
	}
	initialization(data, start);
	launch_philos(data);
	// free(data->philo);
	// free(data);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
		return (core(ac, av));
	else
		return (1);
}
