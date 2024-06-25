/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:22:51 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/06/25 11:48:53 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	error_message(t_info *info)
{
	if (info->error.status == MISSING_ARGS)
		printf(ERROR"Missing arguments\n\033[33m\n\
Usage:\033[0m\
./philo <number of philosophers> <time to die> <time to eat> <time to sleep> \
[number of times each philosopher must eat]\n\n\
Examples:\n\
\t\033[3m./philo 5 400 100 100\033[0m\n\
\t\033[3m./philo 5 50 10 10 5\033[0m\n\
");
	else if (info->error.status == RIP_MALLOC)
		printf(ERROR"An allocation failed in %s:%d\n", \
info->error.file, info->error.line);
	else if (info->error.status == INVALID_NUMBER)
		printf(ERROR"Invalid number, it can't be greater than 999999\n");
	else if (info->error.status == INVALID_PHILO_AMOUNT)
		printf(ERROR"Invalid philosophers amount, it must be between 1-200\n");
	else if (info->error.status == INVALID_TIME_TO_DIE)
		printf(ERROR"Invalid time to die, it must be between 60-999999\n");
	else if (info->error.status == INVALID_TIME_TO_EAT)
		printf(ERROR"Invalid time to eat, it must be between 60-999999\n");
	else if (info->error.status == INVALID_TIME_TO_SLEEP)
		printf(ERROR"Invalid time to sleep, it must be between 60-999999\n");
	else if (info->error.status == INVALID_EAT_AMOUNT)
		printf(ERROR"Invalid eat amount, it must be between 0-999999\n");
}

int	error_handler(t_info *info, int error)
{
	info->error.status = error;
	error_message(info);
	finish_simulation(info);
	return (info->error.status);
}

t_info	*error_set_location(t_info *info, char *file, int line)
{
	info->error.file = file;
	info->error.line = line;
	return (info);
}
