/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:59:42 by iharile           #+#    #+#             */
/*   Updated: 2022/08/29 17:23:04 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*routine(void	*arg)
{
	t_philos	*ph;

	ph = (t_philos*)arg;
	if (ph->name % 2 == 0)
		usleep(50);
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
	ft_printf(ph, "im sleeping");
	ft_usleep(ph->data->time_sleep);
	ft_printf(ph, "im thinking");
}

void	ft_printf(t_philos *ph, char *str)
{
	pthread_mutex_lock(&ph->data->writing);
	printf ("%ld ms %d %s\n", get_time() - ph->data->current_time, ph->name, str);
	pthread_mutex_unlock(&ph->data->writing);
}

int	death_n_meals(t_philos *ph, int total)
{
	int				i;
	int				*arr;
	int				x;

	x = 0;
	arr = malloc (sizeof(int) * total);
	i = -1;
	while (++i < total)
		arr[i] = -1;
	while (1)
	{
		i = -1;
		while (++i < total)
		{
			pthread_mutex_lock(&ph->data->writing);
			if (get_time() - ph[i].last_meal >= ph[i].data->time_die && !ph[i].im_eating)
			{
				printf ("\033[0;31m%ld ms %d is died\033[0m\n", get_time() - ph[i].last_meal, ph[i].name);
				free (arr);
				return (1);
			}
			pthread_mutex_unlock(&ph->data->writing);
			pthread_mutex_lock(&ph->data->writing);
			if (ph[i].meals_count == ph[i].data->must_eat)
			{
				if (arr[i] == -1)
				{
					arr[i] = 1;
					x++;
				}
				if (x == total)
				{
					free (arr);
					return (1);
				}
			}
			pthread_mutex_unlock(&ph->data->writing);
		}
		usleep (10);
	}
}
