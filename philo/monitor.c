/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:50:14 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/07/06 20:31:53 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_death(t_info *info, t_philo *philo)
{
	if (get_elapsed_time() - philo->time_of_eat > info->limit_time_to[DIE]
		&& philo->time_of_eat != -1)
	{
		philo->time_of_death = get_elapsed_time();
		print_message(philo, DIE, true);
		return (true);
	}
	return (false);
}

void	*checker(void *data)
{
	t_info	*info;
	int		index;

	info = data;
	if (info->n_philo == 1)
		return (NULL);
	while (1)
	{
		index = -1;
		while (++index < info->n_philo)
		{
			pthread_mutex_lock(&info->mutex);
			pthread_mutex_lock(&info->table.philo[index].mutex);
			if (check_death(info, &info->table.philo[index]) || info->finish)
			{
				info->finish = true;
				pthread_mutex_unlock(&info->table.philo[index].mutex);
				pthread_mutex_unlock(&info->mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&info->table.philo[index].mutex);
			pthread_mutex_unlock(&info->mutex);
		}
		usleep(100);
	}
	return (NULL);
}
