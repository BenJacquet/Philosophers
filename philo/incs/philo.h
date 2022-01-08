/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:57:02 by jabenjam          #+#    #+#             */
/*   Updated: 2021/12/29 14:56:33 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				die;
	int				eat;
	int				sleep;
	int				meals;
	int				max_meals;
	unsigned long	start;
	unsigned long	last_meal;
	pthread_t		thread;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	active;
}					t_philo;

typedef struct s_data
{
	int				nb;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}				t_data;

/*
**------DEBUG FUNCTIONS---------------------------------------------------------
*/

void	print_data(t_data *data);

/*
**------CORE FUNCTIONS----------------------------------------------------------
*/

int		core(int ac, char **av);

/*
**------PARSING FUNCTIONS-------------------------------------------------------
*/

int		parse_params(int ac, char **av, t_data *data);
int		check_params(t_data *data);

/*
**------UTILITY FUNCTIONS-------------------------------------------------------
*/

int		ft_atoi(const char *str);

// A implementer :

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