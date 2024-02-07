/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:21:48 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/02/07 18:38:53 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	monitor(struct s_philo_info *info, struct s_thread *threads)
{
	long long	current_time;
	int			i;

	while (!are_philo_full(info, threads) && !info->is_dead)
	{
		i = 0;
		while (i < info->philo_count && !info->is_dead)
		{
			current_time = timestamp();
			pthread_mutex_lock(&(threads + i)->eat_lock);
			if (current_time - (threads + i)->last_time_eat > info->time_die_ms)
			{
				if ((threads + i)->eat_count != info->eat_count_max)
				{
					pthread_mutex_lock(&info->is_dead_lock);
					info->is_dead = true;
					pthread_mutex_unlock(&info->is_dead_lock);
					print_state(i + 1, "has died", info->start_time);
				}
			}
			pthread_mutex_unlock(&(threads + i)->eat_lock);
			i++;
		}
	}
}
