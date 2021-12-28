/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:11:13 by jabenjam          #+#    #+#             */
/*   Updated: 2021/07/23 11:11:07 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define FORK "has taken a fork\n"
#define EATS "is eating\n"
#define SLEEPS "is sleeping\n"
#define THINKS "is thinking\n"
#define DIES "died\n"

typedef struct		s_philo
{
	int				id;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
}					t_philo;

typedef struct		s_params
{
	int				nb;
	int				eat;
	int				sleep;
	int				think;
	int				die;
	int				*meals;
	unsigned long	*last_meal;
	int				max_meals;
	pthread_mutex_t *forks;
	t_philo			*philo_data;
}					t_params;



#endif
