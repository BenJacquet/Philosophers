/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:57:02 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/13 17:20:05 by jabenjam         ###   ########.fr       */
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
	int				nb;
	int				die;
	int				eat;
	int				sleep;
	int				meals;
	int				max_meals;
	int				stopped;
	int				ended;
	struct timeval	start;
	struct timeval	last_meal;
	pthread_t		thread;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	active;
	pthread_mutex_t alive;
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
unsigned long	gettime(void);

#endif