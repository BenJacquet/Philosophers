/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:54:36 by jabenjam          #+#    #+#             */
/*   Updated: 2021/12/29 18:00:57 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

// === WORKFLOW ===

// 10
// Prevention des deadlocks et datarace

// 9
// Liberation des ressources du thread (reaper)
// f = pthread_detach()

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

// 5b
// Doit verifier le temps écoulé depuis le dernier repas sur chaque philosophe
// Si un philosophe meurt, doit detach tous les philosophes

// 5a
// Doit check si tous les philosophes ont atteint leur nombre de repas max

// 5
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
		pthread_mutex_init(&data->philo[i].active, NULL);
		data->philo[i].start = (start.tv_sec * 1000) + (start.tv_usec / 1000);
		printf("philosopher %d picks up %p first and %p second\n", data->philo[i].id, data->philo[i].first, data->philo[i].second);
		i++;
	}
	print_data(data);
}

// ms = s * 1000 et us / 1000

unsigned long	timestamp(unsigned long start)
{
	struct timeval	time;
	unsigned long	stamp;

	gettimeofday(&time, NULL);
	stamp = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - start;
	return (stamp);
}

// void	*routine(void *v_philo)
// {
// 	t_philo	*philo;

// 	philo = (t_philo*)v_philo;
// 	while ((philo->meals < philo->max_meals || philo->max_meals == -1) && 1)
// 	{
// 		pthread_mutex_lock(&philo->active);
// 		pthread_mutex_lock(philo->first);
// 		printf("%lums %d has taken a fork\n", timestamp(philo->start), philo->id);
// 		pthread_mutex_lock(philo->second);
// 		printf("%lums %d has taken a fork\n", timestamp(philo->start), philo->id);
// 		printf("%lums %d is eating\n", timestamp(philo->start), philo->id);
// 		// printf("meal number %d, max allowed is %d\n", philo->meals + 1, philo->max_meals);
// 		// pthread_mutex_lock(&philo->active);
// 		philo->meals++;
// 		philo->last_meal = timestamp(philo->start);
// 		// pthread_mutex_unlock(&philo->active);
// 		usleep(philo->eat);
// 		pthread_mutex_unlock(philo->first);
// 		pthread_mutex_unlock(philo->second);
// 		printf("%lums %d is sleeping\n", timestamp(philo->start), philo->id);
// 		usleep(philo->sleep);
// 		printf("%lums %d is thinking\n", timestamp(philo->start), philo->id);
// 		pthread_mutex_unlock(&philo->active);
// 	}
// 	printf("%d took enough meals\n", philo->id);
// 	return ((void*)0);
// }

void	*routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo*)v_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->active);
		pthread_mutex_lock(philo->first);
		printf("%lums %d has taken a fork\n", timestamp(philo->start), philo->id);
		pthread_mutex_lock(philo->second);
		printf("%lums %d has taken a fork\n", timestamp(philo->start), philo->id);
		printf("%lums %d is eating\n", timestamp(philo->start), philo->id);
		// printf("meal number %d, max allowed is %d\n", philo->meals + 1, philo->max_meals);
		// pthread_mutex_lock(&philo->active);
		philo->meals++;
		philo->last_meal = timestamp(philo->start);
		usleep(philo->eat);
		philo->last_meal = timestamp(philo->start);
		// pthread_mutex_unlock(&philo->active);
		pthread_mutex_unlock(philo->first);
		pthread_mutex_unlock(philo->second);
		if (philo->meals == philo->max_meals && philo->max_meals != -1)
			break ;
		printf("%lums %d is sleeping\n", timestamp(philo->start), philo->id);
		usleep(philo->sleep);
		printf("%lums %d is thinking\n", timestamp(philo->start), philo->id);
		pthread_mutex_unlock(&philo->active);
	}
	printf("%d took enough meals\n", philo->id);
	return ((void*)0);
}

int		check_max_meals(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb)
	{
		if (data->philo[i].meals != data->philo[i].max_meals)
			return (0);
		i++;
	}
	return (1);
}

// void	end_sim(t_data *data)
// {

// }

// Verifier le temps depuis le dernier repas pour chaque philosophe


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
			if (timestamp(data->philo[i].last_meal) >= (unsigned long)data->philo[i].die)
			{
				printf("%lums %d has died\n", timestamp(data->philo[i].start), data->philo[i].id);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].active);
			i++;
		}
	}
	//end_sim(data);
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
	// pthread_detach(reaper);
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
