/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:09:33 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/06/25 12:35:28 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	if (!str)
		return (0);
	counter = 0;
	while (str[counter])
		++counter;
	return (counter);
}

size_t	ft_numlen(const char *str)
{
	size_t	counter;
	size_t	index;

	counter = 0;
	index = 0;
	if (!str)
		return (0);
	while (str[index] && str[index] == '0')
		++index;
	while (str[index])
	{
		++index;
		++counter;
	}
	return (counter);
}

int	ft_strncmp(const char *str, const char *str2, size_t bytes)
{
	int	index;

	if (!str || !str2)
		return (-1);
	index = 0;
	while (bytes-- && (str[index] || str2[index]))
	{
		if (str[index] != str2[index])
			return ((unsigned char)str[index] - (unsigned char)str2[index]);
		index++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	number;

	if (!str)
		return (0);
	if (!ft_strncmp(str, "-2147483648", 11))
		return (-2147483648);
	sign = 1;
	while (*str == '\n' || *str == '\t' || *str == '\v' || *str == ' '
		|| *str == '\f' || *str == '\r')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + *str - '0';
		str++;
	}
	return (number * sign);
}
