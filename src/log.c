/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:51 by achu              #+#    #+#             */
/*   Updated: 2025/05/03 00:33:26 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->data->log);
	pthread_mutex_lock(&philo->data->endsim);
	if (philo->data->is_over)
	{
		pthread_mutex_unlock(&philo->data->log);
		pthread_mutex_unlock(&philo->data->endsim);
		return ;
	}
	printf("%li     ", get_time_ms() - philo->data->time_start);
	printf("%i ", philo->id);
	printf("%s\n", status);
	pthread_mutex_unlock(&philo->data->endsim);
	pthread_mutex_unlock(&philo->data->log);
}

bool	check_death(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&philo->data->endsim);
	is_dead = philo->data->is_over;
	if (!is_dead)
	{
		if (get_time_ms() - philo->last_meal > philo->data->time_die)
		{
			log_status(philo, "died");
			philo->data->is_over = true;
			is_dead = true;
		}
	}
	pthread_mutex_unlock(&philo->data->endsim);
	return (is_dead);
}
