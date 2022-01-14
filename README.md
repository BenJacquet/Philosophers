// === WORKFLOW ===

// 9 OK
// Prevention des deadlocks, datarace et lock-order inversions

// 8 OK
// Liberation des ressources du thread (philosophe) apres sa routine
// Liberation des mutex (fourchettes, alive et active)
// Free des ressources malloc

// 7b OK
// Doit verifier le temps écoulé depuis le dernier repas sur chaque philosophe
// Si un philosophe meurt, doit detach tous les philosophes

// 7a OK
// Doit check si tous les philosophes ont atteint leur nombre de repas max

// 7 OK
// Join du thread (superviseur)

// 6 OK
// Creation du thread superviseur (reaper)
//  - Doit avoir les adresses de tous les philosophes
//  - Doit tuer les philosophes
//  - Doit tout clean apres max repas
//  - Doit tuer les philosophes si l' un d'eux meurt de faim

// 5a OK
// Routine des philos :
//  - Prendre une fourchette
//  - Prendre l'autre fourchette
//  - Manger
//  - Lacher la premiere fourchette
//  - Lacher la deuxieme fourchette
//  - Dormir
//  - Penser
//  - Arreter

// 5 OK
// Detach des threads (philosophes)

// 4 OK
// Creation et initialisation des threads (philosophes)
//  - Chacun doit avoir un pointeur vers ses fourchettes

// 3 OK
// Creation et initialisation des mutex (fourchettes)
// - Tableau contenant toutes les fourchettes

// 2 OK
// Gestion d'erreurs
//  - Aucun philosophe
//  - Valeur invalide
//  - Mauvais nombre d'arguments

// 1 OK
// Parsing des arguments : parse_arguments()
//  - Nombre de philosophes
//  - Temps pour mourir
//  - Temps pour manger
//  - Temps pour dormir
//  - Nombre de repas max (OPTIONNEL)