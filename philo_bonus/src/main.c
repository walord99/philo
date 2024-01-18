/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:58:41 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/01/18 16:44:11 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_sprocess(struct s_process *process, struct s_philo_info *info, int pos)
{
	process->eat_count = 0;
	process->is_dead = false;
	process->last_eat_time = info->start_time;
	process->pos = pos;
	process->info = info;
	pthread_mutex_init(&process->eat_lock, NULL);
}

void *death_thread(void *arg)
{
	struct s_process *process = (struct s_process *)arg;

	while (1)
	{
		pthread_mutex_lock(&process->eat_lock);
		if (process->eat_count >= process->info->eat_count_max)
		{
			pthread_mutex_unlock(&process->eat_lock);
			break;
		}
		if (timestamp() - process->last_eat_time > process->info->time_die_ms)
		{
			print_state(process->pos, "died", process->info->start_time);
			break;
		}
	}
}

void	philo(struct s_philo_info *info, int pos, sem_t *d, sem_t *f)
{
	struct s_process process;

	init_sprocess(&process, info, pos);
	while(process.eat_count != info->eat_count_max)
	{
		sem_wait(f);
		print_state(pos, "has taken a fork", info->start_time);
		sem_wait(f);
		print_state(pos, "has taken a fork", info->start_time);
		pthread_mutex_lock(&process.eat_lock);
		print_state(pos, "is eating", info->start_time);
		process.eat_count++;
		process.last_eat_time = timestamp();
		pthread_mutex_unlock(&process.eat_lock);
		usleep(info->time_eat_ms * 1000);
		sem_post(f);
		sem_post(f);
		print_state(pos, "is sleeping", info->start_time);
		usleep(info->time_sleep_ms * 1000);
		print_state(pos, "is thinking", info->start_time);
	}
}

int	main(int argc, char **argv)
{
	struct s_philo_info	info;
	int					i;
	sem_t				*is_dead;
	sem_t				*forks;

	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_FORK);
	if (get_args(argc - 1, &argv[1], &info) != 0)
		return (1);
	i = 0;
	is_dead = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
	forks = sem_open(SEM_FORK, O_CREAT, 0644, info.philo_count);
	info.start_time = timestamp();
	while (i < info.philo_count)
	{
		if (!fork())
		{
			philo(&info, i + 1, is_dead, forks);
			sem_close(is_dead);
			sem_close(forks);
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < info.philo_count)
	{
		waitpid(0, NULL, 0);
		i++;
	}	
	printf("all child done\n");
	sem_close(is_dead);
	sem_close(forks);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_FORK);
}
