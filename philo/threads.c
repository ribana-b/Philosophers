/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:48:05 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/07/06 20:27:49 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*edge_routine(void *data)
{
	t_philo	*philo;

	philo = data;
	print_message(philo, TAKING_FORK, false);
	my_sleep(philo->info->limit_time_to[DIE]);
	philo->time_of_death = get_elapsed_time();
	print_message(philo, DIE, false);
	return (NULL);
}

int	create_threads(t_info *info)
{
	int	index;

	index = 0;
	if (info->n_philo == 1)
	{
		if (pthread_create(&info->table.philo[index].thread, NULL,
				&edge_routine, &info->table.philo[index]) != OK)
			return (error_handler(info, KO));
	}
	else
	{
		while (index < info->n_philo)
		{
			if (pthread_create(&info->table.philo[index].thread, NULL,
					&routine, &info->table.philo[index]) != OK)
				return (error_handler(info, KO));
			++index;
		}
	}
	return (OK);
}

void	join_threads(t_info *info)
{
	int	index;

	index = 0;
	while (index < info->n_philo)
	{
		pthread_join(info->table.philo[index].thread, NULL);
		++index;
	}
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = data;
	if (philo->id % 2 != 0)
		usleep(60 * philo->info->n_philo);
	while (1)
	{
		pthread_mutex_lock(&philo->info->mutex);
		if (quick_check(philo, false))
		{
			pthread_mutex_unlock(&philo->info->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->mutex);
		pthread_mutex_lock(&philo->info->mutex);
		if (philo->meal_counter == philo->info->n_meals)
		{
			philo->info->finish = true;
			pthread_mutex_unlock(&philo->info->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->mutex);
		take_forks(philo);
		start_eating(philo);
		start_sleeping(philo);
		pthread_mutex_lock(&philo->mutex);
		philo->last_meal = get_elapsed_time();
		pthread_mutex_unlock(&philo->mutex);
		start_thinking(philo);
	}
	return (NULL);
}
