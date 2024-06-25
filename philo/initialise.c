/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:21:48 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/06/25 12:42:08 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	initialise_philos(t_info *info)
{
	(void) info;
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
	info->table.forks = malloc(info->n_philo * sizeof(*info->table.forks));
	if (!info->table.forks)
		return (error_handler(error_set_location(info, __FILE__, __LINE__ - 2),
				RIP_MALLOC));
	while (++index < info->n_philo)
		if (pthread_mutex_init(&info->table.forks[index], NULL) != OK)
			return (error_handler(info, RIP_MUTEX));
	return (OK);
}

int	initialise_info(t_info *info)
{
	info->n_philo = ft_atoi(info->argv[1]);
	if (initialise_table(info) != OK)
		return (info->error.status);
	if (initialise_philos(info) != OK)
		return (info->error.status);
	return (OK);
}
