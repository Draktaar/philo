/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:35:09 by achu              #+#    #+#             */
/*   Updated: 2025/04/23 02:26:11 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MULTI		1000

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	int					time_eat;
	int					time_sleep;
	int					time_think;

	pthread_t			thread;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
}	t_philo;

typedef struct s_vars
{
	t_philo				*philos;
	pthread_mutex_t		*fork;
	pthread_mutex_t		log;
	bool				is_death;
}	t_vars;

#endif