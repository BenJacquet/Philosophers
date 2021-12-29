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

// 7a
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

// 6
// Lancement des threads
// f = pthread_join()

// 5
// Creation du thread superviseur (reaper)
//  - Doit avoir les adresses de tous les philosophes
//  - Doit tuer les philosophes
//  - Doit tout clean apres max repas
//  - Doit tuer les philosophes si l' un d'eux meurt de faim
// f = pthread_create()
// r = *reaper

// 4
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

// ajouter repas max et actuels (peut etre sous forme d' un tableau du reaper)
void	initialization(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->nb));
	data->philo = malloc(sizeof(t_philo) * (data->nb));
	while (i < data->nb)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		printf("fork number %d address is %p\n", i, &data->forks[i]);
		i++;
	}
	i = 0;
	while (i < data->nb)
	{
		data->philo[i].id = i;
		// if (i % 2)
		// {
			data->philo->first = &data->forks[i];
			data->philo->second = &data->forks[(i + 1) % data->nb];
		// }
		// else
		// {
		// 	data->philo->first = &data->forks[(i + 1) % data->nb];
		// 	data->philo->second = &data->forks[i];
		// }
		printf("philosopher %d uses %p as first fork and %p as second fork\n", data->philo[i].id, data->philo[i].first, data->philo[i].second);
		i++;
	}
}

int	core(int ac, char **av)
{
	t_data			*data;

	data = malloc(sizeof(t_data));
	if (parse_params(ac, av, data) == 1)
		return (1);
	initialization(data);
	print_data(data);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
		return (core(ac, av));
	else
		return (1);
}
