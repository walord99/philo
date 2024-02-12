/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:21:48 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/02/12 15:15:02 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(struct s_thread *thread, struct s_philo_info *info)
{
	if (timestamp() - (thread)->last_time_eat > info->time_die_ms)
	{
		pthread_mutex_lock(&info->is_dead_lock);
		info->is_dead = true;
		print_state(thread->pos, "has died", info->start_time);
		pthread_mutex_unlock(&info->is_dead_lock);
		return (true);
	}
	return (false);
}

void	monitor(struct s_philo_info *info, struct s_thread *threads)
{
	bool	are_philo_full;
	int		i;

	are_philo_full = false;
	while (!are_philo_full && !info->is_dead)
	{
		are_philo_full = true;
		i = 0;
		while (i < info->philo_count)
		{
			pthread_mutex_lock(&(threads + i)->eat_lock);
			if ((threads + i)->eat_count != info->eat_count_max)
			{
				are_philo_full = false;
				if (is_dead(threads + i, info))
					break ;
			}
			pthread_mutex_unlock(&(threads + i)->eat_lock);
			i++;
		}
	}
}
