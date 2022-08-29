/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:29:52 by iharile           #+#    #+#             */
/*   Updated: 2022/08/29 21:18:56 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_death(t_philos *ph, int i, int *arr)
{
	long			time;
	pthread_mutex_t	write;

	pthread_mutex_init(&write, NULL);
	pthread_mutex_lock(&write);
	if (get_time() - ph[i].last_meal >= ph[i].data->time_die
		&& !ph[i].im_eating)
	{
		time = get_time() - ph[i].last_meal;
		printf ("\033[0;31m%ld ms %d is died\033[0m\n", time, ph[i].name);
		free (arr);
		return (1);
	}
	pthread_mutex_unlock(&write);
	return (0);
}

int	check_meals(t_philos *ph, int i, int *arr)
{
	int	x;

	x = 0;
	pthread_mutex_lock(&ph->data->writing);
	if (ph[i].meals_count == ph[i].data->must_eat)
	{
		if (arr[i] == -1)
		{
			arr[i] = 1;
			x++;
		}
		if (x == ph[i].data->number_of_philo)
		{
			free (arr);
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
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philos	*ph;
	t_data		frk;
	int			i;

	if (ac < 5 || ac > 6 || check_err(av))
	{
		printf ("you need to check all your argements\n");
		return (0);
	}
	if (ac == 6 && ft_atoi(av[5]) == 0)
		return (0);
	i = -1;
	ph = malloc(sizeof(t_philos) * ft_atoi(av[1]));
	if (!ph)
		return (0);
	initialize_data(ph, &frk, av);
	while (++i < ft_atoi(av[1]))
	{
		pthread_create(&ph[i].philos, NULL, &routine, &ph[i]);
		usleep (1);
	}
	death_n_meals(ph, ft_atoi(av[1]));
	return (0);
}
