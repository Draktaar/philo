/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:49:54 by achu              #+#    #+#             */
/*   Updated: 2025/04/24 03:19:19 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup_philo(t_vars *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (data->philos[i].id % 2 == 0)
			usleep(1000);
		i++;
	}
}

void	init_philo(t_vars *data, void *(func)(void *))
{
	int	i;

	i = 0;
	while (i < data->num_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->log, NULL);
	pthread_mutex_init(&data->m_over, NULL);
	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meal_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left = &data->forks[i];
		data->philos[i].right = &data->forks[(i + 1) % data->num_philo];
		pthread_create(&data->philos[i].thread, NULL, func, &data->philos[i]);
		i++;
	}
}

t_vars	*init_data(char **av)
{
	t_vars	*data;

	data = (t_vars *)malloc(sizeof(t_vars));
	if (!data)
		return (NULL);
	data->num_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->num_meal = -1;
	data->is_dead = false;
	data->time_start = get_time_ms();
	data->philos = malloc(data->num_philo * sizeof(t_philo));
	data->forks = malloc(data->num_philo * sizeof(pthread_mutex_t));
	if (!data->philos || !data->forks)
	{
		free_ptr((void *)data->philos);
		return (free(data), NULL);
	}
	return (data);
}
