/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:29:52 by iharile           #+#    #+#             */
/*   Updated: 2022/09/04 11:45:28 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	destroy_mutex(t_philos *ph)
{
	int	i;

	i = -1;
	while (++i < ph->data->number_of_philo)
		pthread_mutex_destroy(&ph->data->forks[i]);
	free (ph->data->forks);
	pthread_mutex_destroy(&ph->data->writing);
}

int	check_death(t_philos *ph, int i, int *arr)
{
	pthread_mutex_lock(&ph->data->writing);
	if (get_time() - ph[i].last_meal >= ph[i].data->time_die
		&& !ph[i].im_eating)
	{
		printf ("\033[0;31m%ld ms %d is died\033[0m\n",
			get_time() - ph[i].start_time, ph[i].name);
		free (arr);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->writing);
	return (0);
}

int	check_meals(t_philos *ph, int i, int *arr)
{
	static int	x;

	(void)arr;
	pthread_mutex_lock(&ph->data->writing);
	if (ph[i].data->must_eat != -1
		&& ph[i].meals_count >= ph[i].data->must_eat)
	{
		if (arr[i] == -1)
		{
			arr[i] = 1;
			x++;
		}
		if (x == ph[i].data->number_of_philo)
		{
			x = 0;
			free (arr);
			printf ("\033[0;34mEND OF SIMULATION\033[0m\n");
			return (1);
		}
	}
	pthread_mutex_unlock(&ph->data->writing);
	return (0);
}

int	death_n_meals(t_philos *ph, int total)
{
	int				i;
	int				*arr;

	arr = malloc (sizeof(int) * total);
	if (!arr)
		return (1);
	i = -1;
	while (++i < total)
		arr[i] = -1;
	while (1)
	{
		i = -1;
		while (++i < total)
		{
			if (check_death(ph, i, arr))
				return (1);
			else if (check_meals(ph, i, arr))
				return (1);
		}
		usleep (10);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philos	*ph;
	t_data		*frk;
	int			i;

	if (check_err(ac, av) == -1)
		return (0);
	i = -1;
	ph = malloc(sizeof(t_philos) * ft_atoi(av[1]));
	if (!ph)
		return (0);
	frk = malloc(sizeof(t_data));
	if (!frk)
		return (0);
	initialize_data(ph, frk, av);
	while (++i < ph->data->number_of_philo)
	{
		pthread_create(&ph[i].philos, NULL, &routine, &ph[i]);
		usleep(10);
	}
	death_n_meals(ph, ft_atoi(av[1]));
	destroy_mutex(ph);
	return (0);
}
