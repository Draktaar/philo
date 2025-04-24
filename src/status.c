/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:51 by achu              #+#    #+#             */
/*   Updated: 2025/04/24 00:51:23 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_status(t_philo philo, const char *status)
{
	pthread_mutex_lock(&philo.data->log);
	printf("%li     ", get_time_ms() - philo.data->time_start);
	printf("%i ", philo.id);
	printf("%s\n", status);
	pthread_mutex_unlock(&philo.data->log);
}
