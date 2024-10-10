/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:56:40 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/10/10 03:04:16 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	apply_colors(int id, int n_philo)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (id + 6) * 27 % 255;
	g = (id + 27) * 3 % 255;
	b = (id + 3) % 255;
	if (n_philo / 2 < id + 1)
	{
		g = (id + 50) % 255;
		b = (id + 80) % 255;
	}
	if (b < 50)
		b = (b * id * id) % 255;
	if (id % 2 == 0)
		b = (r + g + b) % 255;
	printf("\e[0;48;2;%d;%d;%dm", r, g, b);
	if (g > 127 || (r > 127 && b > 127))
		printf("\e[30m");
	else
		printf("\e[37m");
}

static void	reset_color(void)
{
	printf("\e[0m\n");
}

static void	print_the_actual_message(t_philo *philo)
{
	if (philo->status == DIE)
		printf("\e[1;38;2;170;20;20m%8lu %11d died              ",
			philo->time_of_death, philo->id + 1);
	if (philo->status == TAKING_FORK)
		printf("%8lu %11d has taken a fork  ", get_elapsed_time(),
			philo->id + 1);
	if (philo->status == EAT)
		printf("%8lu %11d is eating         ", philo->time_of_eat,
			philo->id + 1);
	else if (philo->status == SLEEP)
		printf("%8lu %11d is sleeping       ", philo->time_of_sleep,
			philo->id + 1);
	else if (philo->status == THINK)
		printf("%8lu %11d is thinking       ", get_elapsed_time(),
			philo->id + 1);
}

int	print_message(t_philo *philo, int state, bool is_monitor)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (!is_monitor)
	{
		pthread_mutex_lock(&philo->info->mutex);
		if (philo->info->finish)
		{
			pthread_mutex_unlock(&philo->info->mutex);
			pthread_mutex_unlock(&philo->info->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->info->mutex);
	}
	philo->status = state;
	apply_colors(philo->id, philo->info->n_philo);
	print_the_actual_message(philo);
	reset_color();
	pthread_mutex_unlock(&philo->info->print_mutex);
	return (0);
}
