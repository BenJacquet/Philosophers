/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:21:17 by jabenjam          #+#    #+#             */
/*   Updated: 2021/12/29 14:46:18 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	print_data(t_data *data)
{
	printf("number of philosophers=%d\n", data->nb);
	printf("time to die=%d\n", data->die);
	printf("time to eat=%d\n", data->eat);
	printf("time to sleep=%d\n", data->sleep);
	printf("max meals=%d\n", data->max_meals);
}

int	check_params(t_data *data)
{
	if (data->nb <= 0 || data->die < 0 || data->eat < 0
		|| data->sleep < 0 || data->max_meals < 0)
		return (1);
	else
		return (0);
}

int	parse_params(int ac, char **av, t_data *data)
{
	data->nb = ft_atoi(av[1]);
	data->die = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->sleep = ft_atoi(av[4]);
	data->max_meals = 0;
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	return (check_params(data));
}
