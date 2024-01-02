/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:58:03 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/01/02 15:23:47 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct					s_philo_info
{
	int					philo_count;
	int					time_die_ms;
	int					time_eat_ms;
	int					time_sleep_ms;
	int					eat_count_max;
	long long			start_time;
};

struct					s_thread
{
	pthread_t			thread;
	int					pos;
	long long			last_time_eat;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		eat_count_mutex;
	int					eat_count;
	struct s_philo_info	*info;
};

static int				get_args(int argc, char **argv,
							struct s_philo_info *philo);
static void				*philo_thread(void *arg_struct);

pthread_mutex_t	*init_forks(int philo_count)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = ft_calloc(sizeof(pthread_mutex_t), philo_count * 2 + 1);
	if (!forks)
		return (NULL);
	i = 0;
	while (i != philo_count * 2)
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

int	init_threads_struct(struct s_thread **threads, pthread_mutex_t *forks,
		struct s_philo_info *info)
{
	int	i;

	*threads = ft_calloc(sizeof(struct s_thread), info->philo_count);
	i = 0;
	while (i < info->philo_count)
	{
		(*threads)[i].left_fork = forks + i;
		(*threads)[i].right_fork = forks + i + 1;
		(*threads)[i].pos = i + 1;
		(*threads)[i].info = info;
		pthread_mutex_init(&((*threads)[i].eat_count_mutex), NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pthread_mutex_t		*forks;
	struct s_philo_info	philo;
	struct s_thread		*threads;

	if (get_args(argc - 1, &argv[1], &philo) == 1)
		return (1);
	forks = init_forks(philo.philo_count);
	philo.start_time = timestamp();
	init_threads_struct(&threads, forks, &philo);
	pthread_create(&((threads + 0)->thread), NULL, &philo_thread, threads + 0);
	pthread_join((threads + 0)->thread, NULL);
	return (0);
}

void	*philo_thread(void *arg_struct)
{
	struct s_thread	*thread;

	thread = (struct s_thread *)arg_struct;
	while (true)
	{
		pthread_mutex_lock(thread->left_fork);
		print_state(thread->pos, "has taken a fork", thread->info->start_time);
		pthread_mutex_lock(thread->right_fork);
		print_state(thread->pos, "has taken a fork", thread->info->start_time);
		print_state(thread->pos, "is eating", thread->info->start_time);
		thread->last_time_eat = timestamp();
		usleep(thread->info->time_eat_ms * 1000);
		pthread_mutex_unlock(thread->right_fork);
		pthread_mutex_unlock(thread->left_fork);
		print_state(thread->pos, "is sleeping", thread->info->start_time);
		usleep(thread->info->time_sleep_ms * 1000);
		print_state(thread->pos, "is thinking", thread->info->start_time);
	}
	return (NULL);
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
	if (error_flag)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}
