/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:05:11 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/07/05 22:56:24 by ribana-b         ###   ########.fr       */
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

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->info->table.forks[philo->forks[RIGHT]]);
		print_message(philo, TAKING_FORK);
		pthread_mutex_lock(&philo->info->table.forks[philo->forks[LEFT]]);
		print_message(philo, TAKING_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->info->table.forks[philo->forks[LEFT]]);
		print_message(philo, TAKING_FORK);
		pthread_mutex_lock(&philo->info->table.forks[philo->forks[RIGHT]]);
		print_message(philo, TAKING_FORK);
	}
	pthread_mutex_unlock(&philo->info->mutex);
	philo->status = TAKING_FORK;
}

void	start_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->time_of_eat = get_elapsed_time();
	pthread_mutex_unlock(&philo->mutex);
	philo->status = EAT;
	print_message(philo, EAT);
	my_sleep(philo->info->limit_time_to[EAT]);
	if (philo->info->n_meals != -1)
	{
		++philo->meal_counter;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->info->table.forks[philo->forks[LEFT]]);
		pthread_mutex_unlock(&philo->info->table.forks[philo->forks[RIGHT]]);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->table.forks[philo->forks[RIGHT]]);
		pthread_mutex_unlock(&philo->info->table.forks[philo->forks[LEFT]]);
	}
}

void	start_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->time_of_sleep = get_elapsed_time();
	pthread_mutex_unlock(&philo->mutex);
	philo->status = SLEEP;
	print_message(philo, SLEEP);
	my_sleep(philo->info->limit_time_to[SLEEP]);
}

void	start_thinking(t_philo *philo)
{
	if (philo->status != EAT && philo->status != SLEEP)
		return ;
	philo->status = THINK;
	print_message(philo, THINK);
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
		if (philo->meal_counter == philo->info->n_meals || philo->info->finish)
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

bool	check_death(t_info *info, t_philo *philo)
{
	return (philo->last_meal - philo->time_of_eat > info->limit_time_to[DIE]);
}

void	*checker(void *data)
{
	t_info	*info;
	int		index;

	info = data;
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

int	start_simulation(t_info *info)
{
	t_pthread	checker_thread;
	int			index;

	index = 0;
	info->start = get_elapsed_time();
	printf("%ld\n", info->limit_time_to[DIE]);
	while (index < info->n_philo)
	{
		if (pthread_create(&info->table.philo[index].thread, NULL,
				&routine, &info->table.philo[index]) != OK)
			return (error_handler(info, KO));
		++index;
	}
	if (pthread_create(&checker_thread, NULL, &checker, info))
		return (KO);
	index = 0;
	while (index < info->n_philo)
	{
		pthread_join(info->table.philo[index].thread, NULL);
		++index;
	}
	pthread_join(checker_thread, NULL);
	return (OK);
}

int	finish_simulation(t_info *info)
{
	int		index;

	index = 0;
	while (++index < info->n_philo && info->error.status != RIP_MALLOC)
	{
		pthread_mutex_destroy(&info->table.forks[index]);
		pthread_mutex_destroy(&info->table.philo[index].mutex);
	}
	pthread_mutex_destroy(&info->mutex);
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->table.mutex);
	free(info->table.forks);
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
