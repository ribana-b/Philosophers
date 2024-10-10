/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:40:07 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/10/10 02:10:23 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_single_fork(t_philo *philo, int side)
{
	pthread_mutex_lock(&philo->info->table.fork[philo->fork[side]]);
	pthread_mutex_lock(&philo->mutex);
	philo->fork_taken[side] = true;
	pthread_mutex_unlock(&philo->mutex);
}

void	leave_single_fork(t_philo *philo, int side)
{
	pthread_mutex_unlock(&philo->info->table.fork[philo->fork[side]]);
	pthread_mutex_lock(&philo->mutex);
	philo->fork_taken[side] = false;
	pthread_mutex_unlock(&philo->mutex);
}

bool	safe_take_fork_odd(t_philo *philo)
{
	take_single_fork(philo, L);
	pthread_mutex_lock(&philo->info->mutex);
	if (!is_simulation_still_running(philo))
	{
		pthread_mutex_unlock(&philo->info->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->mutex);
	print_message(philo, TAKING_FORK, false);
	take_single_fork(philo, R);
	pthread_mutex_lock(&philo->info->mutex);
	if (!is_simulation_still_running(philo))
	{
		pthread_mutex_unlock(&philo->info->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->mutex);
	print_message(philo, TAKING_FORK, false);
	return (false);
}

bool	safe_take_fork_even(t_philo *philo)
{
	take_single_fork(philo, R);
	pthread_mutex_lock(&philo->info->mutex);
	if (!is_simulation_still_running(philo))
	{
		pthread_mutex_unlock(&philo->info->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->mutex);
	print_message(philo, TAKING_FORK, false);
	take_single_fork(philo, L);
	pthread_mutex_lock(&philo->info->mutex);
	if (!is_simulation_still_running(philo))
	{
		pthread_mutex_unlock(&philo->info->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->mutex);
	print_message(philo, TAKING_FORK, false);
	return (false);
}
