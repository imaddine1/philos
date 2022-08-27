/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:59:42 by iharile           #+#    #+#             */
/*   Updated: 2022/08/27 13:27:30 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eat(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->forks[ph->l_f]);
	ft_printf(ph, "");
	pthread_mutex_lock(&ph->data->forks[ph->r_f]);

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
