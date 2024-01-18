/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:36:24 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/01/18 16:38:29 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SEM_DEAD "death"
# define SEM_FORK "forks"

struct					s_philo_info
{
	int					philo_count;
	int					time_die_ms;
	int					time_eat_ms;
	int					time_sleep_ms;
	int					eat_count_max;
	long long			start_time;
};

struct					s_process
{
	pthread_mutex_t		eat_lock;
	long long			last_eat_time;
	int					eat_count;
	struct s_philo_info	*info;
	bool 				is_dead;
	int pos;
};

void					*ft_calloc(size_t type_size, size_t n);
int						ft_atoi(const char *str);
size_t					ft_strlen(const char *str);
int						get_args(int argc, char **argv,
							struct s_philo_info *philo);
long long				timestamp(void);
void					print_state(int philo_num, char *message,
							long long start_time);

#endif