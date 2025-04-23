/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:34:55 by achu              #+#    #+#             */
/*   Updated: 2025/04/23 02:30:15 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*print(void *arg)
{
	char	*test;

	test = (char *)arg;
	usleep(250 * MULTI);
	printf("%s\n", test);
}

int	main(int argc, char **argv)
{
	pthread_t	one;
	pthread_t	two;

	pthread_create(&one, NULL, print, "test22");
	pthread_create(&two, NULL, print, "test");

	pthread_detach(one);
	pthread_detach(two);

	usleep (1000 * MULTI);
	return (0);
}
