/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:58:41 by bplante/Wal       #+#    #+#             */
/*   Updated: 2024/01/08 23:03:06 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo(struct s_philo_info *info, int pos, sem_t *d, sem_t *f)
{
	sem_wait(d);
	sleep(pos);
	d->__align++;
	printf("%i\n", d->__align);
	sem_post(d);
}

int	main(int argc, char **argv)
{
	struct s_philo_info	info;
	int					i;
	sem_t				*is_dead;
	sem_t				*forks;

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
	sem_post(is_dead);
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
