/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:21:17 by jabenjam          #+#    #+#             */
/*   Updated: 2022/01/11 16:38:04 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	print_data(t_data *data)
{
	printf("number of philosophers=%d\n", data->nb);
	printf("time to die=%dms\n", data->philo[0].die);
	printf("time to eat=%dms\n", data->philo[0].eat);
	printf("time to sleep=%dms\n", data->philo[0].sleep);
	printf("max meals=%d\n---------------------\n", data->philo[0].max_meals);
}

int	check_params(t_data *data)
{
	if (data->philo[0].die < 0 || data->philo[0].eat < 0
		|| data->philo[0].sleep < 0
		|| (data->philo[0].max_meals < 0 && data->philo[0].max_meals != -1))
		return (1);
	else
		return (0);
}
int	parse_params(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	
	data->nb = ft_atoi(av[1]);
	if (data->nb <= 0)
		return (1);
	data->philo = malloc(sizeof(t_philo) * (data->nb + 1));
	while (i < data->nb)
	{
		data->philo[i].id = i + 1;
		data->philo[i].die = ft_atoi(av[2]);
		data->philo[i].eat = ft_atoi(av[3]);
		data->philo[i].sleep = ft_atoi(av[4]);
		data->philo[i].meals = 0;
		data->philo[i].max_meals = -1;
		data->philo[i].life = 1;
		if (ac == 6)
			data->philo[i].max_meals = ft_atoi(av[5]);
		i++;
	}
	return (check_params(data));
}
