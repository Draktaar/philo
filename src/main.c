/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:34:55 by achu              #+#    #+#             */
/*   Updated: 2025/04/24 03:29:37 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(int ac, char **av)
{
	t_vars		*data;
	int			i;

	if (ac < 5)
		return (ft_perror("Error: Not enough arguments"), false);
	else if (ac > 6)
		return (ft_perror("Error: Too much arguments"), false);
	i = 0;
	data = init_data(av);
	if (!data)
		return (1);
	if (data->num_philo == 1)
	{
		printf("0    0 died\n");
		free_ptr((void *)data->philos);
		free_ptr((void *)data->forks);
		free(data);
		return (0);
	}
	if (ac == 6)
		data->num_meal = ft_atoi(av[5]);
	init_philo(data, routine);
	while (i < data->num_philo)
		pthread_join(data->philos[i++].thread, NULL);
	clean_data(data);
	return (0);
}
