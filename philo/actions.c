/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:00:14 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/07/07 00:16:15 by ribana-b         ###   ########.com      */
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

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->info->table.fork[philo->fork[R]]);
		take_single_fork(philo, R);
		pthread_mutex_lock(&philo->info->mutex);
		if (quick_check(philo))
		{
			pthread_mutex_unlock(&philo->info->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->info->mutex);
		print_message(philo, TAKING_FORK, false);
		pthread_mutex_lock(&philo->info->table.fork[philo->fork[L]]);
		take_single_fork(philo, L);
		pthread_mutex_lock(&philo->info->mutex);
		if (quick_check(philo))
		{
			pthread_mutex_unlock(&philo->info->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->info->mutex);
		print_message(philo, TAKING_FORK, false);
	}
	else
	{
		pthread_mutex_lock(&philo->info->table.fork[philo->fork[L]]);
		take_single_fork(philo, L);
		pthread_mutex_lock(&philo->info->mutex);
		if (quick_check(philo))
		{
			pthread_mutex_unlock(&philo->info->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->info->mutex);
		print_message(philo, TAKING_FORK, false);
		pthread_mutex_lock(&philo->info->table.fork[philo->fork[R]]);
		take_single_fork(philo, R);
		pthread_mutex_lock(&philo->info->mutex);
		if (quick_check(philo))
		{
			pthread_mutex_unlock(&philo->info->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->info->mutex);
		print_message(philo, TAKING_FORK, false);
	}
}

void	leave_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (philo->fork_taken[L])
			pthread_mutex_unlock(&philo->info->table.fork[philo->fork[L]]);
		leave_single_fork(philo, L);
		if (philo->fork_taken[R])
			pthread_mutex_unlock(&philo->info->table.fork[philo->fork[R]]);
		leave_single_fork(philo, R);
	}
	else
	{
		if (philo->fork_taken[R])
			pthread_mutex_unlock(&philo->info->table.fork[philo->fork[R]]);
		leave_single_fork(philo, R);
		if (philo->fork_taken[L])
			pthread_mutex_unlock(&philo->info->table.fork[philo->fork[L]]);
		leave_single_fork(philo, L);
	}
}

void	start_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex);
	if (quick_check(philo))
	{
		pthread_mutex_unlock(&philo->info->mutex);
		leave_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->info->mutex);
	pthread_mutex_lock(&philo->mutex);
	philo->time_of_eat = get_elapsed_time();
	pthread_mutex_unlock(&philo->mutex);
	leave_forks(philo);
	if (print_message(philo, EAT, false))
		return ;
	my_sleep(philo->info->limit_time_to[EAT]);
	if (philo->info->n_meals != -1)
		++philo->meal_counter;
}

void	start_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex);
	if (quick_check(philo))
	{
		pthread_mutex_unlock(&philo->info->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->info->mutex);
	pthread_mutex_lock(&philo->mutex);
	philo->time_of_sleep = get_elapsed_time();
	pthread_mutex_unlock(&philo->mutex);
	if (print_message(philo, SLEEP, false) == 1)
		return ;
	my_sleep(philo->info->limit_time_to[SLEEP]);
}

void	start_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex);
	if (quick_check(philo))
	{
		pthread_mutex_unlock(&philo->info->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->info->mutex);
	if (philo->info->n_philo % 2 == 0)
		philo->time_of_think = philo->info->limit_time_to[EAT]
			- philo->info->limit_time_to[SLEEP];
	else
		philo->time_of_think = philo->info->limit_time_to[EAT] * 2
			- philo->info->limit_time_to[SLEEP];
	if (philo->time_of_think < 0)
		philo->time_of_think = 0;
	if (print_message(philo, THINK, false) == 1)
		return ;
	my_sleep(philo->time_of_think);
}
