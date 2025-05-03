/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:34:55 by achu              #+#    #+#             */
/*   Updated: 2025/05/03 04:18:14 by achu             ###   ########.fr       */
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

	if (!init_arg(ac, av))
		return (EXIT_FAILURE);
	data = init_data(av);
	if (!data)
		return (EXIT_FAILURE);
	if (ac == 6)
		data->num_meal = ft_atoi(av[5]);
	if (!init_philo(data, routine))
		return (clean_data(data), EXIT_FAILURE);
	i = 0;
	while (i < data->num_philo)
		pthread_join(data->philos[i++].thread, NULL);
	clean_data(data);
	if (ac == 6 && !data->is_over)
		printf("Each philosopher ate %d times\n", data->num_meal);
	return (EXIT_SUCCESS);
}
