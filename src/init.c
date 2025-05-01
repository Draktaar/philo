/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:49:54 by achu              #+#    #+#             */
/*   Updated: 2025/05/02 00:05:09 by achu             ###   ########.fr       */
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

bool	init_arg(int ac, char **av)
{
	if (ac < 5)
		return (ft_perror("Error: Not enough arguments"), false);
	else if (ac > 6)
		return (ft_perror("Error: Too much arguments"), false);
	else if (ft_atoi(av[1]) <= 0)
		return (ft_perror("Error: Not enough philosopher"), false);
	else if (ft_atoi(av[1]) == 1)
		return (printf("1    1 died\n"), false);
	else if (ft_atoi(av[2]) < 60)
		return (ft_perror("Error: Not enough time to die"), false);
	else if (ft_atoi(av[3]) < 60)
		return (ft_perror("Error: Not enough time to eat"), false);
	else if (ft_atoi(av[4]) < 60)
		return (ft_perror("Error: Not enough time to sleep"), false);
	else if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (ft_perror("Error: Not enough meal"), false);
	return (true);
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
