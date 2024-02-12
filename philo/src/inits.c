/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:25:35 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/02/12 14:59:10 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	init_threads_struct(struct s_thread **threads, pthread_mutex_t *forks,
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
