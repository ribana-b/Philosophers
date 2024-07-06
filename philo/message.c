/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:56:40 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/07/06 20:08:19 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	apply_color(t_philo *philo)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = 20;
	g = (philo->id + 60 * 2) % 255;
	b = (philo->id + 20 * 2) % 255;
	if (philo->info->n_philo / 2 < philo->id)
	{
		g = (philo->id + 50) % 255;
		b = (philo->id + 80) % 255;
	}
	printf("\e[0;48;2;%d;%d;%dm", r, g, b);
	if (g > 127)
		printf("\e[30m");
	else
		printf("\e[37m");
}

static void	reset_color(void)
{
	printf("\e[0m\n");
}

int	print_message(t_philo *philo, int state, bool is_monitor)
{
	(void)is_monitor;
	pthread_mutex_lock(&philo->info->print_mutex);
	philo->status = state;
	apply_color(philo);
	if (state == DIE)
		printf("\e[38;2;170;20;20m%8lu %11d died              ",
			philo->time_of_death, philo->id + 1);
	if (state == TAKING_FORK)
		printf("%8lu %11d has taken a fork  ", get_elapsed_time(),
			philo->id + 1);
	if (state == EAT)
		printf("%8lu %11d is eating         ", philo->time_of_eat,
			philo->id + 1);
	else if (state == SLEEP)
		printf("%8lu %11d is sleeping       ", philo->time_of_sleep,
			philo->id + 1);
	else if (state == THINK)
		printf("%8lu %11d is thinking       ", get_elapsed_time(),
			philo->id + 1);
	reset_color();
	pthread_mutex_unlock(&philo->info->print_mutex);
	return (0);
}
