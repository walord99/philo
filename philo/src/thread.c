/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:27:18 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/01/11 01:40:39 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(struct s_thread *th, char *msg, int sleep_ms)
{
	if (!th->info->is_dead)
	{
		print_state(th->pos, msg, th->info->start_time);
		if (sleep_ms)
			usleep(sleep_ms * 1000);
	}
}

void	*philo_thread(void *arg_struct)
{
	struct s_thread	*th;

	th = (struct s_thread *)arg_struct;
	while (th->eat_count != th->info->eat_count_max && !th->info->is_dead)
	{
		if (!th->info->is_dead)
			pthread_mutex_lock(th->left_fork);
		log_state(th, "has taken a fork", 0);
		if (!th->info->is_dead)
			pthread_mutex_lock(th->right_fork);
		log_state(th, "has taken a fork", 0);
		pthread_mutex_lock(&th->eat_lock);
		th->eat_count++;
		th->last_time_eat = timestamp();
		log_state(th, "is eating", th->info->time_eat_ms);
		pthread_mutex_unlock(&th->eat_lock);
		pthread_mutex_unlock(th->right_fork);
		pthread_mutex_unlock(th->left_fork);
		log_state(th, "is sleeping", th->info->time_sleep_ms);
		log_state(th, "is thinking", 0);
	}
	return (NULL);
}
