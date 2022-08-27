/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:59:42 by iharile           #+#    #+#             */
/*   Updated: 2022/08/27 16:30:59 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eat(t_philos *ph)
{
	pthread_mutex_t	writing;

	pthread_mutex_init(&writing, NULL);
	pthread_mutex_lock(&ph->data->forks[ph->l_f]);
	ft_printf(ph, "has taken a fork");
	pthread_mutex_lock(&ph->data->forks[ph->r_f]);
	ft_printf(ph, "has taken a fork");
	pthread_mutex_lock(&writing);
	ph->im_eating = 1;
	ph->meals_count += 1;
	pthread_mutex_unlock(&writing);
	ft_usleep(ph->data->time_eat);
	ph->data->current_time = get_time();
	pthread_mutex_lock(&writing);
	ph->im_eating = 0;
	pthread_mutex_unlock(&writing);
	pthread_mutex_unlock(&ph->data->forks[ph->r_f]);
	pthread_mutex_unlock(&ph->data->forks[ph->l_f]);

}

void	sleep_n_think(t_philos *ph)
{
	ft_printf(ph, "im sleeping");
	ft_usleep(ph->data->time_sleep);
	ft_printf(ph, "im thinking");
}

void	ft_printf(t_philos *ph, char *str)
{
	pthread_mutex_t	writing;

	pthread_mutex_init(&writing, NULL);
	pthread_mute_lock(&writing);
	printf ("%ld ms %d %s\n", ph->data->current_time, ph->name, str);
	pthread_mute_unlock(&writing, NULL);
}

void	death_n_meals(t_philos *ph, int total)
{
	int				i;
	pthread_mutex_t	writing;
	int				*arr;
	int				x;

	x = 0;
	pthread_mutex_init(&writing, NULL);
	arr = malloc (sizeof(int) * total);
	i = -1;
	while (++i < total)
		arr[i] = -1;
	while (1)
	{
		pthread_mutex_lock(&writing);
		if (get_time() - ph->data->current_time >= ph->data->time_die && !ph->im_eating)
		{
			printf ("%ld ms %d is died\n", get_time() - ph->data->current_time, ph->name);
			i = -1;
			while (++i < total)
				pthread_detach(ph[i].philos);
			return ;
		}
		if (ph->meals_count == total)
		{
			if (arr[ph->name - 1] == -1)
			{
				arr[ph->name - 1] = 1;
				x++;
			}
			if (x == total)
			{
				printf ("END OF SIMULATION\n");
				i = -1;
				while (++i < total)
					pthread_detach(ph[i].philos);
				return ;
			}
		}
		pthread_mutex_unlock(&writing);
	}
}
