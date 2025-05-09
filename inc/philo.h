/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:35:09 by achu              #+#    #+#             */
/*   Updated: 2025/05/07 11:58:34 by achu             ###   ########.fr       */
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
	pthread_t			thread;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	int					meal_eaten;
	long				last_meal;
	struct s_vars		*data;
}	t_philo;

typedef struct s_vars
{
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_meal;
	bool				is_dead;

	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		log;

	long				time_start;
	pthread_mutex_t		m_over;
}	t_vars;

// Initialize
t_vars		*init_data(char **av);
bool		init_arg(int ac, char **av);
bool		init_philo(t_vars *data, void *(func)(void *));

// Philo
void		*routine(void *arg);
bool		check_death(t_philo *philo);

// Clean-up
void		clean_data(t_vars *data);
void		free_ptr(void *ptr);

// Helper
int			ft_atoi(const char *str);
bool		is_digit(int ac, char **av);
void		log_status(t_philo *philo, const char *status);
long		get_time_ms(void);
long		time_remaining(t_philo *philo);
void		ft_perror(const char *s);

#endif