/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:59:42 by iharile           #+#    #+#             */
/*   Updated: 2022/09/04 11:48:06 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*routine(void	*arg)
{
	t_philos	*ph;

	ph = (t_philos *)arg;
	if (ph->name % 2 == 0)
		usleep(100);
	while (1)
	{
		eat(ph);
	}
	return (NULL);
}

void	eat(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->forks[ph->l_f]);
	ft_printf(ph, "has taken a fork");
	pthread_mutex_lock(&ph->data->forks[ph->r_f]);
	ft_printf(ph, "has taken a fork");
	ft_printf(ph, "\033[32m is eating\033[0m");
	pthread_mutex_lock(&ph->data->writing);
	ph->im_eating = 1;
	ph->meals_count += 1;
	ph->last_meal = get_time();
	pthread_mutex_unlock(&ph->data->writing);
	ft_usleep(ph->data->time_eat);
	pthread_mutex_lock(&ph->data->writing);
	ph->im_eating = 0;
	pthread_mutex_unlock(&ph->data->writing);
	pthread_mutex_unlock(&ph->data->forks[ph->l_f]);
	pthread_mutex_unlock(&ph->data->forks[ph->r_f]);
	ft_printf(ph, "is sleeping");
	ft_usleep(ph->data->time_sleep);
	ft_printf(ph, "is thinking");
}

long	get_time(void)
{
	struct timeval	time;
	long			start_time;

	if (gettimeofday(&time, NULL) != 0)
	{
		printf ("gettimeofday failed\n");
		return (-1);
	}
	start_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (start_time);
}

void	ft_printf(t_philos *ph, char *str)
{
	pthread_mutex_lock(&ph->data->writing);
	printf ("%ld ms %d %s\n", get_time() - ph->start_time,
		ph->name, str);
	pthread_mutex_unlock(&ph->data->writing);
}

void	ft_usleep(long duration)
{
	long	start;

	start = get_time();
	while (get_time() - start < duration)
		usleep(300);
}
