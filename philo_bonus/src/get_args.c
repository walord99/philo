/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:12:53 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/01/08 22:35:27 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_string_int(char *str, int sign);
int			ft_isdigit(int c);

bool	is_valid_positive_int(char *str)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	while (str[i] == '0')
		i++;
	if ((ft_strlen(&str[i]) == 10 && !is_string_int(&str[i], sign))
		|| ft_strlen(&str[i]) > 10)
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_string_int(char *str, int sign)
{
	int		i;
	char	*max_int;

	max_int = "2147483647";
	i = 0;
	while (i < 9)
	{
		if (str[i] > max_int[i])
			return (false);
		if (str[i] < max_int[i])
			return (true);
		i++;
	}
	if (sign > 0 && str[i] > max_int[i])
		return (false);
	else if (str[i] > max_int[i] + 1)
		return (false);
	return (true);
}

void	check_then_store(int *store_place, char *str, bool *error_flag)
{
	if (*error_flag == false && is_valid_positive_int(str))
		*store_place = ft_atoi(str);
	else
		*error_flag = true;
}

int	get_args(int argc, char **argv, struct s_philo_info *philo)
{
	bool	error_flag;

	if (argc != 4 && argc != 5)
		return (1);
	error_flag = false;
	check_then_store(&philo->philo_count, argv[0], &error_flag);
	check_then_store(&philo->time_die_ms, argv[1], &error_flag);
	check_then_store(&philo->time_eat_ms, argv[2], &error_flag);
	check_then_store(&philo->time_sleep_ms, argv[3], &error_flag);
	if (argc == 5)
		check_then_store(&philo->eat_count_max, argv[4], &error_flag);
	else
		philo->eat_count_max = -1;
	if (error_flag)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}
