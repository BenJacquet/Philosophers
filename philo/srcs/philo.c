#include "../incs/philo.h"

// === WORKFLOW ===

// 10
// Prevention des deadlocks et datarace

// 9
// Liberation des ressources du thread (reaper)
// f = pthread_detach()

// 8
// Liberation des ressources du thread (philosophe) apres sa routine
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
//  - Doit tuer les philosophes et tout nettoyer si ils ont atteint leur max de repas
//  - Doit tuer les philosophes si l' un d'eux meurt de faim
// f = pthread_create()
// r = *reaper

// 4
// Creation et initialisation des threads (philosophes)
//  - Chacun doit avoir un pointeur vers ses fourchettes
// f = pthread_create()
// r = *philosophers

// 3
// Creation et initialisation des mutex (fourchettes)
// - Tableau contenant toutes les fourchettes
// f = pthread_mutex_init()
// r = *forks

// 2
// Gestion d'erreurs
//  - Aucun philosophe
//  - Valeur invalide
//  - Mauvais nombre d'arguments
// f = check_arguments()


// 1
// Parsing des arguments : parse_arguments()
//  - Nombre de philosophes
//  - Temps pour mourir
//  - Temps pour manger
//  - Temps pour dormir
//  - Nombre de repas max (OPTIONNEL)
// f = parse_arguments()
// r = args[]

int main(int ac, char **av)
{
    
}