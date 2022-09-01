/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:59:42 by iharile           #+#    #+#             */
/*   Updated: 2022/09/01 12:47:19 by iharile          ###   ########.fr       */
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
		sleep_n_think(ph);
	}
	return (NULL);
}

void	eat(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->forks[ph->l_f]);
	ft_printf(ph, "has taken a fork");
	pthread_mutex_lock(&ph->data->forks[ph->r_f]);
	ft_printf(ph, "has taken a fork");
	ft_printf(ph, "\033[32mim eating\033[0m");
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
}

void	sleep_n_think(t_philos *ph)
{
	ft_printf(ph, "is sleeping");
	ft_usleep(ph->data->time_sleep);
	ft_printf(ph, "is thinking");
}

void	ft_printf(t_philos *ph, char *str)
{
	long	time;

	pthread_mutex_lock(&ph->data->writing);
	time = get_time() - ph->data->current_time;
	printf ("%ld ms %d %s\n", time, ph->name, str);
	pthread_mutex_unlock(&ph->data->writing);
}

void	ft_usleep(long duration)
{
	long	start;

	start = get_time();
	while (get_time() - start < duration)
		usleep(300);
}
