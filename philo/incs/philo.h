#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>

// A implementer :

// parse_arguments(int ac, char **av)
// check_arguments(data *args)
// create_forks(data *args)
// init_philos(pthread_mutex_t *forks, data *args)
// create_philos(pthread_t *philos_t)
// create_reaper(philo *philos)
// routine(philo philo[n])
// ft_sleep(int duration);
// take_forks()
// eat()
// drop_forks()
// sleep()
// clean_philos(philo *philos)
// clean_reaper(philo *reaper)

#endif