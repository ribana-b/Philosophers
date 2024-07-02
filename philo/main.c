/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:05:11 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/07/01 11:45:16 by ribana-b         ###   ########.com      */
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
	int	index[2];

	pthread_mutex_lock(&philo->info->mutex);
	index[LEFT] = philo->id % philo->info->n_philo;
	index[RIGHT] = (philo->id + 1) % philo->info->n_philo;
	pthread_mutex_unlock(&philo->info->mutex);
	if (index[LEFT] < index[RIGHT])
	{
		pthread_mutex_lock(&philo->info->table.forks[index[LEFT]]);
		print_message(philo, TAKING_FORK);
		pthread_mutex_lock(&philo->info->table.forks[index[RIGHT]]);
		print_message(philo, TAKING_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->info->table.forks[index[RIGHT]]);
		print_message(philo, TAKING_FORK);
		pthread_mutex_lock(&philo->info->table.forks[index[LEFT]]);
		print_message(philo, TAKING_FORK);
	}
	philo->status = TAKING_FORK;
}

void	start_eating(t_philo *philo)
{
	philo->time_of[EAT] = get_elapsed_time();
	philo->status = EAT;
	print_message(philo, EAT);
	my_sleep(philo->info->limit_time_to[EAT]);
	if (philo->info->n_meals != -1)
		++philo->meal_counter;
}

void	leave_forks(t_philo *philo)
{
	int	index[2];

	pthread_mutex_lock(&philo->info->mutex);
	index[LEFT] = philo->id % philo->info->n_philo;
	index[RIGHT] = (philo->id + 1) % philo->info->n_philo;
	pthread_mutex_unlock(&philo->info->mutex);
	pthread_mutex_unlock(&philo->info->table.forks[index[RIGHT]]);
	pthread_mutex_unlock(&philo->info->table.forks[index[LEFT]]);
}

void	start_sleeping(t_philo *philo)
{
	philo->time_of[SLEEP] = get_elapsed_time();
	philo->status = SLEEP;
	print_message(philo, SLEEP);
	pthread_mutex_lock(&philo->info->mutex);
	my_sleep(philo->info->limit_time_to[SLEEP]);
	pthread_mutex_unlock(&philo->info->mutex);
}

void	start_thinking(t_philo *philo)
{
	if (philo->status != EAT && philo->status != SLEEP)
		return ;
	philo->status = THINK;
	print_message(philo, THINK);
}

bool	finished_meals(t_info *info)
{
	int		index;
	bool	is_finished;

	index = 0;
	is_finished = true;
	while (index < info->n_philo && is_finished)
	{
		if (info->table.philo[index].meal_counter != info->n_meals)
			is_finished = false;
		++index;
	}
	return (is_finished);
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = data;
	while (1)
	{
		take_forks(philo);
		start_eating(philo);
		leave_forks(philo);
		start_sleeping(philo);
		start_thinking(philo);
		if (philo->meal_counter == philo->info->n_meals)
			break ;
	}
	return (NULL);
}

int	create_simulation_threads(t_info *info)
{
	int	index;

	index = 0;
	while (index < info->n_philo)
	{
		if (pthread_create(&info->table.philo[index].thread, NULL,
				&routine, &info->table.philo[index]) != OK)
			return (error_handler(info, KO));
		++index;
	}
	return (OK);
}

void	join_simulation_threads(t_info *info)
{
	int	index;

	index = 0;
	while (index < info->n_philo)
	{
		pthread_join(info->table.philo[index].thread, NULL);
		++index;
	}
}

void	*checker(void *data)
{
	t_info	*info;
	int		index;
	bool	finished;

	info = data;
	index = 0;
	finished = true;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNICE\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	pthread_mutex_lock(&info->mutex);
	while (index < info->n_philo && finished)
	{
		if (info->table.philo[index].meal_counter != info->n_meals)
			finished = false;
		++index;
	}
	pthread_mutex_unlock(&info->mutex);
	if (!finished)
		return (NULL);
	info->finish = true;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNICE\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	return (info);
}

int	start_simulation(t_info *info)
{
	//t_pthread	thread;

	info->finish = false;
	if (create_simulation_threads(info) != OK)
		return (KO);
	join_simulation_threads(info);
	//if (pthread_create(&thread, NULL, &checker, info) != OK)
	//	return (KO);
	//pthread_join(thread, NULL);
	return (OK);
}

int	finish_simulation(t_info *info)
{
	int		index;

	index = 0;
	while (++index < info->n_philo && info->error.status != RIP_MALLOC)
	{
		pthread_mutex_destroy(&info->table.forks[index]);
	}
	pthread_mutex_destroy(&info->mutex);
	pthread_mutex_destroy(&info->print_mutex);
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
