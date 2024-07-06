/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:21:48 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/07/06 16:34:51 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	initialise_philos(t_info *info)
{
	int	index;

	index = -1;
	while (++index < info->n_philo)
	{
		info->table.philo[index].is_alive = true;
		info->table.philo[index].fork[L] = index;
		info->table.philo[index].fork[R] = (index + 1) % info->n_philo;
		info->table.philo[index].fork_taken[L] = false;
		info->table.philo[index].fork_taken[R] = false;
		info->table.philo[index].id = index;
		info->table.philo[index].meal_counter = 0;
		info->table.philo[index].info = info;
		info->table.philo[index].time_of_eat = -1;
		info->table.philo[index].time_of_death = -1;
		info->table.philo[index].time_of_sleep = -1;
		info->table.philo[index].time_of_think = -1;
		if (pthread_mutex_init(&info->table.philo[index].mutex, NULL) != OK)
			return (error_handler(info, RIP_MUTEX));
	}
	return (OK);
}

static int	initialise_table(t_info *info)
{
	int	index;

	index = -1;
	info->table.philo = malloc(info->n_philo * sizeof(*info->table.philo));
	if (!info->table.philo)
		return (error_handler(error_set_location(info, __FILE__, __LINE__ - 2),
				RIP_MALLOC));
	info->table.fork = malloc(info->n_philo * sizeof(*info->table.fork));
	if (!info->table.fork)
		return (error_handler(error_set_location(info, __FILE__, __LINE__ - 2),
				RIP_MALLOC));
	while (++index < info->n_philo)
		if (pthread_mutex_init(&info->table.fork[index], NULL) != OK)
			return (error_handler(info, RIP_MUTEX));
	return (OK);
}

int	initialise_info(t_info *info)
{
	info->n_philo = ft_atoi(info->argv[1]);
	info->limit_time_to[DIE] = ft_atot(info->argv[2]);
	info->limit_time_to[EAT] = ft_atot(info->argv[3]);
	info->limit_time_to[SLEEP] = ft_atot(info->argv[4]);
	info->n_meals = -1;
	info->finish = false;
	if (info->argc == 6)
		info->n_meals = ft_atoi(info->argv[5]);
	if (initialise_table(info) != OK)
		return (info->error.status);
	if (initialise_philos(info) != OK)
		return (info->error.status);
	if (pthread_mutex_init(&info->mutex, NULL) != OK)
		return (error_handler(info, RIP_MUTEX));
	if (pthread_mutex_init(&info->print_mutex, NULL) != OK)
		return (error_handler(info, RIP_MUTEX));
	if (pthread_mutex_init(&info->monitor_mutex, NULL) != OK)
		return (error_handler(info, RIP_MUTEX));
	return (OK);
}
