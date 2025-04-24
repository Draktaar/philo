/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 02:03:27 by achu              #+#    #+#             */
/*   Updated: 2025/04/24 14:38:56 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_death(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&philo->data->m_over);
	is_dead = philo->data->is_dead;
	if (!is_dead)
	{
		if (get_time_ms() - philo->last_meal > philo->data->time_die)
		{
			log_status(*philo, "died");
			philo->data->is_dead = true;
			is_dead = true;
		}
	}
	pthread_mutex_unlock(&philo->data->m_over);
	return (is_dead);
}

static bool	check_thinking(t_philo *philo)
{
	if (check_death(philo))
		return (false);
	log_status(*philo, "is thinking");
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left);
		log_status(*philo, "has taken a fork");
		pthread_mutex_lock(philo->right);
		log_status(*philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right);
		log_status(*philo, "has taken a fork");
		pthread_mutex_lock(philo->left);
		log_status(*philo, "has taken a fork");
	}
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (false);
	}
	return (true);
}

static bool	check_eating(t_philo *philo)
{
	long	start;

	if (check_death(philo))
		return (false);
	log_status(*philo, "is eating");
	philo->last_meal = get_time_ms();
	usleep(philo->data->time_eat * MULTI);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	philo->meal_eaten++;
	if (philo->data->num_meal != -1 && philo->meal_eaten >= philo->data->num_meal)
		return (false);
	return (true);
}

static bool	check_sleeping(t_philo *philo)
{
	long	start;

	if (check_death(philo))
		return (false);
	log_status(*philo, "is sleeping");
	start = get_time_ms();
	usleep(philo->data->time_sleep * MULTI);
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(1000);
	philo->last_meal = get_time_ms();
	while (!check_death(philo))
	{
		if (!check_thinking(philo))
			break ;
		if (!check_eating(philo))
			break ;
		if (!check_sleeping(philo))
			break ;
	}
	return (NULL);
}
