/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:05:11 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/07/06 23:15:56 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	quick_check(t_philo *philo)
{
	if (philo->info->finish)
	{
		if ((philo->status == EAT || philo->status == TAKING_FORK)
			&& philo->id % 2 == 0)
		{
			if (philo->fork_taken[L])
				pthread_mutex_unlock(&philo->info->table.fork[philo->fork[L]]);
			philo->fork_taken[L] = false;
			if (philo->fork_taken[R])
				pthread_mutex_unlock(&philo->info->table.fork[philo->fork[R]]);
			philo->fork_taken[R] = false;
		}
		else if ((philo->status == EAT || philo->status == TAKING_FORK)
			&& philo->id % 2 != 0)
		{
			if (philo->fork_taken[R])
				pthread_mutex_unlock(&philo->info->table.fork[philo->fork[R]]);
			philo->fork_taken[R] = false;
			if (philo->fork_taken[L])
				pthread_mutex_unlock(&philo->info->table.fork[philo->fork[L]]);
			philo->fork_taken[L] = false;
		}
		return (true);
	}
	return (false);
}

static int	parse_arguments(t_info *info)
{
	int	counter;
	int	number;

	counter = 0;
	while (++counter < info->argc)
	{
		number = ft_atoi(info->argv[counter]);
		if (ft_numlen(info->argv[counter]) > 6)
			return (error_handler(info, INVALID_NUMBER));
		if (counter == 1 && (number < MIN_PHILO || number > MAX_PHILO))
			return (error_handler(info, INVALID_PHILO_AMOUNT));
		else if (counter == 2 && (number < MIN_TIME || number > MAX_TIME))
			return (error_handler(info, INVALID_TIME_TO_DIE));
		else if (counter == 3 && (number < MIN_TIME || number > MAX_TIME))
			return (error_handler(info, INVALID_TIME_TO_EAT));
		else if (counter == 4 && (number < MIN_TIME || number > MAX_TIME))
			return (error_handler(info, INVALID_TIME_TO_SLEEP));
		else if (counter == 5 && (number < MIN_EATS || number > MAX_EATS))
			return (error_handler(info, INVALID_EAT_AMOUNT));
	}
	return (OK);
}

int	start_simulation(t_info *info)
{
	t_pthread	checker_thread;

	info->start = get_elapsed_time();
	if (create_threads(info) != OK)
		return (info->error.status);
	if (pthread_create(&checker_thread, NULL, &checker, info))
		return (error_handler(info, KO));
	usleep(100 * info->n_philo);
	join_threads(info);
	pthread_join(checker_thread, NULL);
	return (OK);
}

int	finish_simulation(t_info *info)
{
	int		index;

	index = 0;
	usleep(100 * info->n_philo);
	while (++index < info->n_philo && info->error.status != RIP_MALLOC)
	{
		pthread_mutex_destroy(&info->table.fork[index]);
		pthread_mutex_destroy(&info->table.philo[index].mutex);
	}
	pthread_mutex_destroy(&info->mutex);
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->monitor_mutex);
	free(info->table.fork);
	free(info->table.philo);
	return (info->error.status);
}

int	main(int argc, char **argv)
{
	static t_info	info;

	info.argc = argc;
	info.argv = argv;
	if (argc != 5 && argc != 6)
		return (error_handler(&info, MISSING_ARGS));
	if (parse_arguments(&info) != OK)
		return (info.error.status);
	if (initialise_info(&info) != OK)
		return (info.error.status);
	if (start_simulation(&info) != OK)
		return (info.error.status);
	if (finish_simulation(&info) != OK)
		return (info.error.status);
	return (info.error.status);
}
