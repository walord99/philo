/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:58:01 by bplante/Wal       #+#    #+#             */
/*   Updated: 2023/12/30 15:12:08 by bplante/Wal      ###   ########.fr       */
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

void		print_state(int philo_num, char *message, long long start_time);
long long	timestamp(void);
bool		is_valid_positive_int(char *str);

void		*ft_calloc(size_t type_size, size_t n);
int			ft_atoi(const char *str);

size_t		ft_strlen(const char *str);

#endif