/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:57:02 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/17 17:48:23 by jabenjam         ###   ########.fr       */
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
}					t_philo;

typedef struct s_data
{
	int				nb;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}				t_data;

/*
**------CORE FUNCTIONS----------------------------------------------------------
*/

int				core(int ac, char **av);
void			launch_philos(t_data *data);
void			cleanup(t_data *data);

/*
**------INIT FUNCTIONS---------------------------------------------------------
*/

void			initialization(t_data *data, struct timeval start);
void			initialization_two(t_data *data, struct timeval start);

/*
**------ROUTINE FUNCTIONS-------------------------------------------------------
*/

void			*wrapper(void *v_philo);
int				routine(t_philo *philo);
int				action(t_philo *philo, int code);
void			print_action(const char *action, t_philo *philo, int code);
void			end_philo(t_philo *philo, int code);

/*
**------SUPERVISOR FUNCTIONS----------------------------------------------------
*/

void			*supervisor(void *v_data);
int				check_starvation(t_data *data, int i);
void			end(t_data *data);
void			stop(t_data *data);

/*
**------PARSING FUNCTIONS-------------------------------------------------------
*/

int				parse_params(int ac, char **av, t_data *data);
int				check_params(t_data *data);
void			print_data(t_data *data);

/*
**------UTILITY FUNCTIONS-------------------------------------------------------
*/

unsigned long	gettime(void);
unsigned long	timestamp(struct timeval start);
int				ft_atoi(const char *str);
void			ft_mssleep(unsigned long temps_ms);

#endif