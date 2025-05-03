/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:51 by achu              #+#    #+#             */
/*   Updated: 2025/05/03 04:25:40 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_status(t_philo *philo, const char *status)
{
	bool	is_over;

	pthread_mutex_lock(&philo->data->log);
	is_over = philo->data->is_over;
	if (is_over || get_time_ms() - philo->last_meal > philo->data->time_die)
	{
		pthread_mutex_unlock(&philo->data->log);
		return ;
	}
	printf("%li     ", get_time_ms() - philo->data->time_start);
	printf("%i ", philo->id);
	printf("%s\n", status);
	pthread_mutex_unlock(&philo->data->log);
}

bool	check_death(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&philo->data->log);
	is_dead = philo->data->is_over;
	if (!is_dead && get_time_ms() - philo->last_meal > philo->data->time_die)
	{
		philo->data->is_over = true;
		is_dead = true;
		printf("%li     ", get_time_ms() - philo->data->time_start);
		printf("%i died\n", philo->id);
	}
	pthread_mutex_unlock(&philo->data->log);
	return (is_dead);
}
