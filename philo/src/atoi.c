/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:54:38 by bplante/Wal       #+#    #+#             */
/*   Updated: 2023/12/30 14:56:12 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	nb;
	int			sign;

	if (str == NULL)
		return (0);
	i = 0;
	nb = 0;
	sign = 1;
	if (str)
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '-')
			sign = -1;
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (ft_isdigit(str[i]))
			nb = nb * 10 + str[i++] - '0';
	}
	return (sign * nb);
}
