/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 02:03:27 by achu              #+#    #+#             */
/*   Updated: 2025/05/07 11:56:14 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	fork_picking(t_philo *philo,
	pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_lock(left);
	pthread_mutex_lock(right);
	pthread_mutex_lock(&philo->data->log);
	if (check_death(philo))
	{
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(&philo->data->log);
		return (false);
	}
	log_status(philo, "has taken a fork");
	log_status(philo, "has taken a fork");
	log_status(philo, "is eating");
	pthread_mutex_unlock(&philo->data->log);
	return (true);
}

static bool	check_thinking(t_philo *philo)
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	pthread_mutex_lock(&philo->data->log);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->data->log);
		return (false);
	}
	log_status(philo, "is thinking");
	pthread_mutex_unlock(&philo->data->log);
	if (philo->id % 2 == 0)
	{
		left = philo->left;
		right = philo->right;
	}
	else
	{
		usleep(time_remaining(philo) / 3 * 1000);
		left = philo->right;
		right = philo->left;
	}
	if (!fork_picking(philo, left, right))
		return (false);
	return (true);
}

static bool	check_eating(t_philo *philo)
{
	long	start;

	philo->last_meal = get_time_ms();
	usleep(philo->data->time_eat * MULTI);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	philo->meal_eaten++;
	if (philo->data->num_meal != -1
		&& philo->meal_eaten >= philo->data->num_meal)
	{
		pthread_mutex_lock(&philo->data->log);
		if (check_death(philo))
		{
			pthread_mutex_unlock(&philo->data->log);
			return (false);
		}
		log_status(philo, "is thinking");
		pthread_mutex_unlock(&philo->data->log);
		return (false);
	}
	return (true);
}

static bool	check_sleeping(t_philo *philo)
{
	long	start;

	pthread_mutex_lock(&philo->data->log);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->data->log);
		return (false);
	}
	log_status(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->log);
	usleep(philo->data->time_sleep * MULTI);
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time_ms();
	if (philo->data->num_philo == 1)
	{
		pthread_mutex_lock(&philo->data->log);
		log_status(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->data->log);
		pthread_mutex_lock(philo->left);
		while (!check_death(philo))
			usleep(100);
		pthread_mutex_unlock(philo->left);
		return (NULL);
	}
	while (1)
	{
		if (!check_thinking(philo))
			return (NULL);
		if (!check_eating(philo))
			return (NULL);
		if (!check_sleeping(philo))
			return (NULL);
	}
	return (NULL);
}
