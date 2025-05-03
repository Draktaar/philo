/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 02:03:27 by achu              #+#    #+#             */
/*   Updated: 2025/05/03 04:29:08 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	pick_fork(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (check_death(philo))
	{
		pthread_mutex_unlock(first);
		return (false);
	}
	log_status(philo, "has taken a fork");
	pthread_mutex_lock(second);
	if (check_death(philo))
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		return (false);
	}
	log_status(philo, "has taken a fork");
	return (true);
}

static bool	check_thinking(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->left;
		second = philo->right;
	}
	else
	{
		first = philo->right;
		second = philo->left;
	}
	if (!pick_fork(philo, first, second))
		return (false);
	return (true);
}

static bool	check_eating(t_philo *philo)
{
	long	start;

	if (check_death(philo))
		return (false);
	log_status(philo, "is eating");
	philo->last_meal = get_time_ms();
	start = get_time_ms();
	while (get_time_ms() - start <= philo->data->time_eat)
	{
		if (check_death(philo))
		{
			pthread_mutex_unlock(philo->left);
			pthread_mutex_unlock(philo->right);
			return (false);
		}
		usleep(100);
	}
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	philo->meal_eaten++;
	if (philo->data->num_meal != -1
		&& philo->meal_eaten >= philo->data->num_meal)
		return (false);
	return (true);
}

static bool	check_sleeping(t_philo *philo)
{
	long	start;

	if (check_death(philo))
		return (false);
	log_status(philo, "is sleeping");
	start = get_time_ms();
	while (get_time_ms() - start <= philo->data->time_sleep)
	{
		if (check_death(philo))
			return (false);
		usleep(100);
	}
	if (check_death(philo))
		return (false);
	log_status(philo, "is thinking");
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	philo->last_meal = get_time_ms();
	if (philo->data->num_philo == 1)
	{
		pthread_mutex_lock(philo->left);
		log_status(philo, "has taken a fork");
		while (!check_death(philo))
			usleep(100);
		pthread_mutex_unlock(philo->left);
		return (NULL);
	}
	while (1)
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
