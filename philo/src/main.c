/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:58:03 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/02/07 18:46:10 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(pthread_mutex_t *forks, struct s_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		pthread_mutex_unlock(forks + i);
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
