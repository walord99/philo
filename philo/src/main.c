/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:58:03 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/01/03 14:01:19 by bplante/Wal      ###   ########.fr       */
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
	bool				is_dead;
};

struct					s_thread
{
	pthread_t			thread;
	int					pos;
	long long			last_time_eat;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
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

	forks = ft_calloc(sizeof(pthread_mutex_t), philo_count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i != philo_count)
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

void	swap_fork(struct s_thread *thread)
{
	pthread_mutex_t	*temp;

	temp = thread->left_fork;
	thread->left_fork = thread->right_fork;
	thread->right_fork = temp;
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
		(*threads)[i].right_fork = forks + ((i + 1) % info->philo_count);
		(*threads)[i].pos = i + 1;
		(*threads)[i].info = info;
		(*threads)[i].last_time_eat = info->start_time;
		pthread_mutex_init(&(*threads)[i].eat_lock, NULL);
		i++;
	}
}

void	join_all(struct s_thread *threads, struct s_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		pthread_join((threads + i)->thread, NULL);
		i++;
	}
}

bool	are_philo_full(struct s_philo_info *info, struct s_thread *threads)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		pthread_mutex_lock(&(threads + i)->eat_lock);
		if ((threads + i)->eat_count != info->eat_count_max)
		{
			pthread_mutex_unlock(&(threads + i)->eat_lock);
			return (false);
		}
		pthread_mutex_unlock(&(threads + i)->eat_lock);
		i++;
	}
	return (true);
}

int	monitor(struct s_philo_info *info, struct s_thread *threads)
{
	long long	current_time;
	int			i;

	while (!are_philo_full(info, threads) && !info->is_dead)
	{
		i = 0;
		while (i < info->philo_count)
		{
			current_time = timestamp();
			pthread_mutex_lock(&(threads + i)->eat_lock);
			if (current_time - (threads + i)->last_time_eat > info->time_die_ms)
			{
				if ((threads + i)->eat_count != info->eat_count_max)
				{
					print_state(i + 1, "has died", info->start_time);
					info->is_dead = true;
				}
			}
			pthread_mutex_unlock(&(threads + i)->eat_lock);
			i++;
		}
	}
}

void	create_threads(struct s_thread *threads, struct s_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		usleep(50);
		pthread_create(&((threads + i)->thread), NULL, &philo_thread, threads
			+ i);
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
	create_threads(threads, &philo);
	monitor(&philo, threads);
	join_all(threads, &philo);
	free(forks);
	free(threads);
	return (0);
}

void	*philo_thread(void *arg_struct)
{
	struct s_thread	*th;

	th = (struct s_thread *)arg_struct;
	while (th->eat_count != th->info->eat_count_max && !th->info->is_dead)
	{
		pthread_mutex_lock(th->left_fork);
		if (!th->info->is_dead)
			print_state(th->pos, "has taken a fork", th->info->start_time);
		if (!th->info->is_dead)
			print_state(th->pos, "has taken a fork", th->info->start_time);
		pthread_mutex_lock(&th->eat_lock);
		th->eat_count++;
		th->last_time_eat = timestamp();
		pthread_mutex_unlock(&th->eat_lock);
		if (!th->info->is_dead)
		{
			print_state(th->pos, "is eating", th->info->start_time);
			usleep(th->info->time_eat_ms * 1000);
		}
		pthread_mutex_unlock(th->right_fork);
		pthread_mutex_unlock(th->left_fork);
		if (!th->info->is_dead)
		{
			print_state(th->pos, "is sleeping", th->info->start_time);
			usleep(th->info->time_sleep_ms * 1000);
		}
		if (!th->info->is_dead)
		{
			print_state(th->pos, "is thinking", th->info->start_time);
		}
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
	else
		philo->eat_count_max = -1;
	if (error_flag)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	philo->is_dead = false;
	return (0);
}
