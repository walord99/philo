/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:27:18 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/02/12 15:07:56 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(struct s_thread *th)
{
	pthread_mutex_lock(th->left_fork);
	pthread_mutex_lock(&th->info->is_dead_lock);
	if (!th->info->is_dead)
	{
		print_state(th->pos, "has taken a fork", th->info->start_time);
		pthread_mutex_unlock(&th->info->is_dead_lock);
	}
	else
	{
		pthread_mutex_unlock(&th->info->is_dead_lock);
		return (1);
	}
	pthread_mutex_lock(th->right_fork);
	pthread_mutex_lock(&th->info->is_dead_lock);
	if (!th->info->is_dead)
	{
		print_state(th->pos, "has taken a fork", th->info->start_time);
		pthread_mutex_unlock(&th->info->is_dead_lock);
	}
	else
	{
		pthread_mutex_unlock(&th->info->is_dead_lock);
		return (1);
	}
	return (0);
}

int	eat(struct s_thread *th)
{
	pthread_mutex_lock(&th->info->is_dead_lock);
	if (!th->info->is_dead)
	{
		pthread_mutex_lock(&th->eat_lock);
		th->eat_count++;
		th->last_time_eat = timestamp();
		print_state(th->pos, "is eating", th->info->start_time);
		pthread_mutex_unlock(&th->eat_lock);
		pthread_mutex_unlock(&th->info->is_dead_lock);
	}
	else
	{
		pthread_mutex_unlock(&th->info->is_dead_lock);
		return (1);
	}
	usleep(th->info->time_eat_ms * 1000);
	pthread_mutex_unlock(th->right_fork);
	pthread_mutex_unlock(th->left_fork);
	return (0);
}

int	sleep_action(struct s_thread *th)
{
	pthread_mutex_lock(&th->info->is_dead_lock);
	if (!th->info->is_dead)
	{
		print_state(th->pos, "is sleeping", th->info->start_time);
		pthread_mutex_unlock(&th->info->is_dead_lock);
	}
	else
	{
		pthread_mutex_unlock(&th->info->is_dead_lock);
		return (1);
	}
	usleep(th->info->time_sleep_ms * 1000);
	return (0);
}

int	think(struct s_thread *th)
{
	pthread_mutex_lock(&th->info->is_dead_lock);
	if (!th->info->is_dead)
	{
		print_state(th->pos, "is thinking", th->info->start_time);
		pthread_mutex_unlock(&th->info->is_dead_lock);
	}
	else
	{
		pthread_mutex_unlock(&th->info->is_dead_lock);
		return (1);
	}
	return (0);
}

void	*philo_thread(void *arg_struct)
{
	struct s_thread	*th;

	th = (struct s_thread *)arg_struct;
	while (th->eat_count != th->info->eat_count_max)
	{
		if (take_fork(th) == 1)
			break ;
		if (eat(th) == 1)
			break ;
		if (sleep_action(th) == 1)
			break ;
		if (think(th) == 1)
			break ;
	}
	return (NULL);
}
