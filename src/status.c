/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:51 by achu              #+#    #+#             */
/*   Updated: 2025/05/07 11:14:03 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_status(t_philo *philo, const char *status)
{
	long long int	time;

	if (philo->data->is_dead)
		return ;
	time = get_time_ms() - philo->data->time_start;
	printf("%lli %i %s\n", time, philo->id, status);
}

bool	check_death(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&philo->data->m_over);
	is_dead = philo->data->is_dead;
	if (!is_dead && get_time_ms() - philo->last_meal >= philo->data->time_die)
	{
		log_status(philo, "died");
		philo->data->is_dead = true;
		is_dead = true;
	}
	pthread_mutex_unlock(&philo->data->m_over);
	return (is_dead);
}
