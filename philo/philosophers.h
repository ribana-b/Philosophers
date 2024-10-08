/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:15:16 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/10/10 01:32:22 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* @------------------------------------------------------------------------@ */
/* |                               Includes                                 | */
/* @------------------------------------------------------------------------@ */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdbool.h>

/* @------------------------------------------------------------------------@ */
/* |                                Defines                                 | */
/* @------------------------------------------------------------------------@ */

# define ERROR "\033[31m[ERROR]\033[0m "
# define MAX_TIME 999999
# define MIN_TIME 60
# define MAX_EATS 999999
# define MIN_EATS 0
# define MAX_PHILO 200
# define MIN_PHILO 1

/* @------------------------------------------------------------------------@ */
/* |                                 Types                                  | */
/* @------------------------------------------------------------------------@ */

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef struct s_info	t_info;
typedef struct s_error	t_error;
typedef pthread_mutex_t	t_mutex;
typedef long			t_time;
typedef pthread_t		t_pthread;

/* @------------------------------------------------------------------------@ */
/* |                                 Enums                                  | */
/* @------------------------------------------------------------------------@ */

enum e_error
{
	OK = 0,
	MISSING_ARGS,
	RIP_MALLOC,
	RIP_THREAD,
	RIP_MUTEX,
	INVALID_NUMBER,
	INVALID_PHILO_AMOUNT,
	INVALID_TIME_TO_DIE,
	INVALID_TIME_TO_EAT,
	INVALID_TIME_TO_SLEEP,
	INVALID_EAT_AMOUNT,
	KO,
};

enum e_state
{
	DIE = 0,
	EAT,
	SLEEP,
	THINK,
	TAKING_FORK,
	ALIVE,
};

enum e_forks
{
	L = 0,
	R,
};

/* @------------------------------------------------------------------------@ */
/* |                                Structs                                 | */
/* @------------------------------------------------------------------------@ */

struct	s_error
{
	int		status;
	int		line;
	char	*file;
};

struct	s_table
{
	t_mutex	*fork;
	t_philo	*philo;
};

struct	s_philo
{
	bool		is_alive;
	int			fork[2];
	bool		fork_taken[2];
	int			id;
	int			meal_counter;
	int			status;
	t_time		last_meal;
	t_time		time_of_death;
	t_time		time_of_eat;
	t_time		time_of_sleep;
	t_time		time_of_think;
	t_pthread	thread;
	t_info		*info;
	t_mutex		mutex;
};

struct	s_info
{
	t_time	start;
	bool	is_start;
	int		argc;
	int		n_philo;
	int		n_meals;
	char	**argv;
	t_time	limit_time_to[3];
	t_error	error;
	t_table	table;
	t_mutex	mutex;
	t_mutex	print_mutex;
	t_mutex	monitor_mutex;
	bool	finish;
};

/* @------------------------------------------------------------------------@ */
/* |                               Functions                                | */
/* @------------------------------------------------------------------------@ */

int		error_handler(t_info *info, int error);
t_info	*error_set_location(t_info *info, char *file, int line);
int		initialise_info(t_info *info);
int		finish_simulation(t_info *info);
size_t	ft_strlen(const char *str);
size_t	ft_numlen(const char *str);
int		ft_atoi(const char *str);
t_time	ft_atot(const char *str);
int		ft_strncmp(const char *str, const char *str2, size_t bytes);
t_time	get_elapsed_time(void);
int		print_message(t_philo *philo, int state, bool is_monitor);
void	my_sleep(t_time time_in_ms);
void	take_forks(t_philo *philo);
void	start_eating(t_philo *philo);
void	start_thinking(t_philo *philo);
void	start_sleeping(t_philo *philo);
void	*routine(void *data);
void	*checker(void *data);
int		create_threads(t_info *info);
void	join_threads(t_info *info);
bool	is_simulation_still_running(t_philo *philo);
void	leave_forks(t_philo *philo);
void	take_single_fork(t_philo *philo, int side);
void	leave_single_fork(t_philo *philo, int side);
bool	safe_take_fork_odd(t_philo *philo);
bool	safe_take_fork_even(t_philo *philo);

#endif // PHILOSOPHERS_H
