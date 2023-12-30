/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:58:03 by bplante/Wal       #+#    #+#             */
/*   Updated: 2023/12/30 15:33:38 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct		s_philo
{
	int		philo_count;
	int		time_die_ms;
	int		time_eat_ms;
	int		time_sleep_ms;
	int		eat_count;
};

struct		s_thread_info
{
};

static int	get_args(int argc, char **argv, struct s_philo *philo);

int	main(int argc, char **argv)
{
	long long		start_time;
	pthread_mutex_t	*forks;
	struct s_philo	philo;

	if (get_args(argc - 1, &argv[1], &philo) == 1)
		return (1);
	start_time = timestamp();
	print_state(1, "test", start_time);
}

void	philo_thread(int pos, struct s_thread_info *info)
{
}
void	temp(int *store_place, char *str, bool *error_flag)
{
	if (*error_flag == false && is_valid_positive_int(str))
		*store_place = ft_atoi(str);
	else
		*error_flag = true;
}

int	get_args(int argc, char **argv, struct s_philo *philo)
{
	bool	error_flag;

	error_flag = false;
	temp(&philo->philo_count, argv[0], &error_flag);
	temp(&philo->time_die_ms, argv[1], &error_flag);
	temp(&philo->time_eat_ms, argv[2], &error_flag);
	temp(&philo->time_sleep_ms, argv[3], &error_flag);
	if (argc == 5)
		temp(&philo->eat_count, argv[4], &error_flag);
	if (error_flag)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}
