/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:56:40 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/07/01 11:45:51 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (state == TAKING_FORK || state == THINK)
		printf("%12lu\t\t%3d ", get_elapsed_time(), philo->id);
	else
		printf("%12lu\t\t%3d ", philo->time_of[state], philo->id);
	if (state == DIE)
		printf("died\n");
	else if (state == TAKING_FORK)
		printf("has taken a fork\n");
	else if (state == EAT)
		printf("is eating\n");
	else if (state == SLEEP)
		printf("is sleeping\n");
	else if (state == THINK)
		printf("is thinking\n");
	pthread_mutex_unlock(&philo->info->print_mutex);
}
