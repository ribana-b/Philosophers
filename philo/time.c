/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:40:14 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/06/28 11:10:04 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_time	get_elapsed_time(void)
{
	static struct timeval	start;
	static bool				initialized;
	struct timeval			current;
	t_time					result;

	result = 0;
	if (!initialized)
	{
		gettimeofday(&start, NULL);
		result = start.tv_sec * 1e3 + start.tv_usec / 1000;
		initialized = true;
		return (result - result);
	}
	gettimeofday(&current, NULL);
	result = (current.tv_sec * 1e3 + current.tv_usec * 1e-3)
		-(start.tv_sec * 1e3 + start.tv_usec * 1e-3);
	return (result);
}

void	my_sleep(t_time time_in_ms)
{
	usleep(time_in_ms * 1e3);
}
