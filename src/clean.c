/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:47:11 by achu              #+#    #+#             */
/*   Updated: 2025/05/03 04:26:03 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_ptr(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
}

void	clean_data(t_vars *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->log);
	free_ptr((void *)data->philos);
	free_ptr((void *)data->forks);
	free(data);
}
