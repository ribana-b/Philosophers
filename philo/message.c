/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:56:40 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/07/04 02:40:26 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (state == TAKING_FORK || state == THINK)
		printf("%12lu\t\t%3d ", get_elapsed_time(), philo->id + 1);
	if (state == DIE)
		printf("%12lu\t\t%3d died\n", philo->time_of_death, philo->id + 1);
	else if (state == TAKING_FORK)
		printf("has taken a fork\n");
	else if (state == EAT)
		printf("%12lu\t\t%3d is eating\n", philo->time_of_eat, philo->id + 1);
	else if (state == SLEEP)
		printf("%12lu\t\t%3d is sleeping\n", philo->time_of_sleep, philo->id + 1);
	else if (state == THINK)
		printf("is thinking\n");
	pthread_mutex_unlock(&philo->info->print_mutex);
}
