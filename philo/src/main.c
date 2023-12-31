/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:58:03 by bplante/Wal       #+#    #+#             */
/*   Updated: 2023/12/31 13:49:13 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct				s_philo
{
	int				philo_count;
	int				time_die_ms;
	int				time_eat_ms;
	int				time_sleep_ms;
	int				eat_count_max;
	long long		start_time;
};

struct				s_thread_info
{
	long long		last_time_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*eat_count_mutex;
	int				eat_count;
};

static int			get_args(int argc, char **argv, struct s_philo *philo);

pthread_mutex_t	*init_forks(int size)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = ft_calloc(sizeof(pthread_mutex_t), size + 1);
	if (!forks)
		return (NULL);
	i = 0;
	while (i != size)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	struct s_philo	philo;

	if (get_args(argc - 1, &argv[1], &philo) == 1)
		return (1);
	forks = init_forks(philo.philo_count);
	philo.start_time = timestamp();
}

void	philo_thread(struct s_philo *info, struct s_thread_info *thread)
{
	while (true)
	{
		pthread_mutex_lock(thread->left_fork);
		pthread_mutex_lock(thread->right_fork);
		thread->last_time_eat = timestamp();
		usleep(info->time_eat_ms * 1000);
		pthread_mutex_unlock(thread->right_fork);
		pthread_mutex_unlock(thread->left_fork);
		usleep(info->time_sleep_ms * 1000);
		// write tihnking
	}
}
void	check_then_store(int *store_place, char *str, bool *error_flag)
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
	check_then_store(&philo->philo_count, argv[0], &error_flag);
	check_then_store(&philo->time_die_ms, argv[1], &error_flag);
	check_then_store(&philo->time_eat_ms, argv[2], &error_flag);
	check_then_store(&philo->time_sleep_ms, argv[3], &error_flag);
	if (argc == 5)
		check_then_store(&philo->eat_count_max, argv[4], &error_flag);
	if (error_flag)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}
