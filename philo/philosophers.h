/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:15:16 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/05/23 17:42:49 by ribana-b         ###   ########.com      */
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
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdbool.h>

/* @------------------------------------------------------------------------@ */
/* |                                Defines                                 | */
/* @------------------------------------------------------------------------@ */

# define ERROR "\033[31m[ERROR]\033[0m "
# define MAX_TIME 999999
# define MIN_TIME 0
# define MAX_PHILO 200
# define MIN_PHILO 1

/* @------------------------------------------------------------------------@ */
/* |                                 Types                                  | */
/* @------------------------------------------------------------------------@ */

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef struct s_info	t_info;
typedef struct s_error	t_error;

// Renaming types for name consistency
typedef pthread_mutex_t	t_mutex;
typedef time_t			t_time;

/* @------------------------------------------------------------------------@ */
/* |                                 Enums                                  | */
/* @------------------------------------------------------------------------@ */

enum e_error
{
	OK = 0,
	MISSING_ARGS,
	RIP_MALLOC,
	RIP_MUTEX,
	NOT_VALID_NUMBER,
	KO,
};

enum e_state
{
	EAT = 0,
	SLEEP,
	DIE,
	THINK,
};

enum e_forks
{
	LEFT = 0,
	RIGHT,
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
	t_mutex	*forks;
	t_philo	*philo;
};

struct	s_philo
{
	bool	is_alive;
	bool	forks[2];
	int		id;
	int		meal_counter;
	int		status;
	t_time	last_meal;
	t_time	time_to[3];
};

struct	s_info
{
	int		argc;
	int		n_philo;
	char	**argv;
	t_error	error;
	t_table	table;
};

/* @------------------------------------------------------------------------@ */
/* |                               Functions                                | */
/* @------------------------------------------------------------------------@ */

int		error_handler(t_info *info, int error);
void	error_set_location(t_info *info, char *file, int line);
int		initialise_info(t_info *info);
int		finish_simulation(t_info *info);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *str, const char *str2, size_t bytes);

#endif // PHILOSOPHERS_H
