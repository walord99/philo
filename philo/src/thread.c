/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:27:18 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/02/07 18:45:08 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(struct s_thread *th, char *msg, int sleep_ms)
{
	pthread_mutex_lock(&th->info->is_dead_lock);
	if (!th->info->is_dead)
	{
		pthread_mutex_unlock(&th->info->is_dead_lock);
		print_state(th->pos, msg, th->info->start_time);
		if (sleep_ms)
			usleep(sleep_ms * 1000);
	}
	else
		pthread_mutex_unlock(&th->info->is_dead_lock);
}

void	eat(struct s_thread *th)
{
	pthread_mutex_lock(th->left_fork);
	log_state(th, "has taken a fork", 0);
	pthread_mutex_lock(th->right_fork);
	log_state(th, "has taken a fork", 0);
	pthread_mutex_lock(&th->eat_lock);
	th->eat_count++;
	th->last_time_eat = timestamp();
	log_state(th, "is eating", th->info->time_eat_ms);
	pthread_mutex_unlock(&th->eat_lock);
	pthread_mutex_unlock(th->right_fork);
	pthread_mutex_unlock(th->left_fork);
}

void	*philo_thread(void *arg_struct)
{
	struct s_thread	*th;

	th = (struct s_thread *)arg_struct;
	pthread_mutex_lock(&th->info->is_dead_lock);
	while (th->eat_count != th->info->eat_count_max && !th->info->is_dead)
	{
		pthread_mutex_unlock(&th->info->is_dead_lock);
		eat(th);
		log_state(th, "is sleeping", th->info->time_sleep_ms);
		log_state(th, "is thinking", 0);
		pthread_mutex_lock(&th->info->is_dead_lock);
	}
	pthread_mutex_unlock(&th->info->is_dead_lock);
	return (NULL);
}
