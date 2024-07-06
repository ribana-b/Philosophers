/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:40:07 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/07/07 00:40:12 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_single_fork(t_philo *philo, int side)
{
	pthread_mutex_lock(&philo->mutex);
	philo->fork_taken[side] = true;
	pthread_mutex_unlock(&philo->mutex);
}

void	leave_single_fork(t_philo *philo, int side)
{
	pthread_mutex_lock(&philo->mutex);
	philo->fork_taken[side] = false;
	pthread_mutex_unlock(&philo->mutex);
}

bool	safe_take_fork_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->table.fork[philo->fork[L]]);
	take_single_fork(philo, L);
	pthread_mutex_lock(&philo->info->mutex);
	if (quick_check(philo))
	{
		pthread_mutex_unlock(&philo->info->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->mutex);
	print_message(philo, TAKING_FORK, false);
	pthread_mutex_lock(&philo->info->table.fork[philo->fork[R]]);
	take_single_fork(philo, R);
	pthread_mutex_lock(&philo->info->mutex);
	if (quick_check(philo))
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
	pthread_mutex_lock(&philo->info->table.fork[philo->fork[R]]);
	take_single_fork(philo, R);
	pthread_mutex_lock(&philo->info->mutex);
	if (quick_check(philo))
	{
		pthread_mutex_unlock(&philo->info->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->mutex);
	print_message(philo, TAKING_FORK, false);
	pthread_mutex_lock(&philo->info->table.fork[philo->fork[L]]);
	take_single_fork(philo, L);
	pthread_mutex_lock(&philo->info->mutex);
	if (quick_check(philo))
	{
		pthread_mutex_unlock(&philo->info->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->mutex);
	print_message(philo, TAKING_FORK, false);
	return (false);
}
