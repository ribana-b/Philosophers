/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:50:14 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/10/10 04:32:13 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void check_meals(t_info *info)
{
	int	index;
	int	counter;

	index = -1;
	counter = 0;
	while (++index < info->n_philo)
	{
		pthread_mutex_lock(&info->mutex);
		counter += info->table.philo[index].meal_counter;
		pthread_mutex_unlock(&info->mutex);
	}
	pthread_mutex_lock(&info->mutex);
	if (counter == info->n_meals * info->n_philo)
		info->finish = true;
	pthread_mutex_unlock(&info->mutex);
}

static bool	check_death(t_info *info, t_philo *philo)
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

static bool	check_philosophers(t_info *info)
{
	int		index;

	index = -1;
	while (++index < info->n_philo)
	{
		pthread_mutex_lock(&info->mutex);
		if (info->finish)
		{
			pthread_mutex_unlock(&info->mutex);
			return (true);
		}
		pthread_mutex_unlock(&info->mutex);
		pthread_mutex_lock(&info->table.philo[index].mutex);
		if (check_death(info, &info->table.philo[index]))
		{
			pthread_mutex_lock(&info->mutex);
			info->finish = true;
			pthread_mutex_unlock(&info->mutex);
			pthread_mutex_unlock(&info->table.philo[index].mutex);
			return (true);
		}
		pthread_mutex_unlock(&info->table.philo[index].mutex);
	}
	return (false);
}

void	*checker(void *data)
{
	t_info	*info;

	info = data;
	if (info->n_philo == 1)
		return (NULL);
	while (1)
	{
		check_meals(info);
		if (check_philosophers(info))
			return (NULL);
		my_sleep(100);
	}
	return (NULL);
}
