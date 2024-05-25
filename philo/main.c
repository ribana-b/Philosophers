/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:05:11 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/05/23 18:24:29 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parse_arguments(t_info *info)
{
	int	counter;
	int	number;

	counter = 0;
	while (++counter < info->argc)
	{
		number = ft_atoi(info->argv[counter]);
		if (ft_strlen(info->argv[counter]) > 6)
			return (error_handler(info, NOT_VALID_NUMBER));
		if (counter == 1 && (number < MIN_PHILO || number > MAX_PHILO))
			return (error_handler(info, NOT_VALID_NUMBER));
		else if (number < MIN_TIME || number > MAX_TIME)
			return (error_handler(info, NOT_VALID_NUMBER));
	}
	return (OK);
}

int	start_simulation(t_info *info)
{
	(void) info;
	return (OK);
}

int	finish_simulation(t_info *info)
{
	int	index;

	index = -1;
	free(info->table.philo);
	while (++index < info->n_philo)
	{
		pthread_mutex_destroy(&info->table.forks[index]);
	}
	free(info->table.forks);
	return (OK);
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
	return (OK);
}
