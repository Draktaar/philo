/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:34:55 by achu              #+#    #+#             */
/*   Updated: 2025/05/07 11:53:37 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	init_philo(data, routine);
	i = 0;
	while (i < data->num_philo)
		pthread_join(data->philos[i++].thread, NULL);
	if (ac == 6 && !data->is_dead)
		printf("Each philosopher ate %d times\n", data->num_meal);
	clean_data(data);
	return (EXIT_SUCCESS);
}
