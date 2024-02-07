/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:58:01 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/02/07 18:46:03 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct					s_philo_info
{
	int					philo_count;
	int					time_die_ms;
	int					time_eat_ms;
	int					time_sleep_ms;
	int					eat_count_max;
	long long			start_time;
	bool				is_dead;
	pthread_mutex_t		is_dead_lock;
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

void					print_state(int philo_num, char *message,
							long long start_time);
long long				timestamp(void);
void					*ft_calloc(size_t type_size, size_t n);
int						ft_atoi(const char *str);
size_t					ft_strlen(const char *str);
void					monitor(struct s_philo_info *info,
							struct s_thread *threads);
int						get_args(int argc, char **argv,
							struct s_philo_info *philo);
pthread_mutex_t			*init_forks(int philo_count);
void					init_threads_struct(struct s_thread **threads,
							pthread_mutex_t *forks, struct s_philo_info *info);

void					*philo_thread(void *arg_struct);

#endif