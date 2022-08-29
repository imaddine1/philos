/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:34:55 by iharile           #+#    #+#             */
/*   Updated: 2022/08/29 16:32:18 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	initialize_data(t_philos *ph, t_data *frk, char **av)
{
	int	i;
	int	total;	


	total = ft_atoi(av[1]);
	pthread_mutex_init(&frk->writing, NULL);
	frk->forks = malloc(sizeof(pthread_mutex_t) * total);
	if (!frk->forks)
	{
		printf ("malloc failed\n");	
		return ;
	}
	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_mutex_init(&frk->forks[i], NULL);
	frk->number_of_philo = ft_atoi(av[1]);
	frk->time_die = ft_atoi(av[2]);
	frk->time_eat = ft_atoi(av[3]);
	frk->time_sleep = ft_atoi(av[4]);
	frk->must_eat = ft_atoi(av[5]);
	frk->current_time = get_time();
	i = -1;
	while (++i < total)
	{
		ph[i].name = i + 1;
		ph[i].im_eating = 0;
		ph[i].meals_count = 0;
		ph[i].last_meal = get_time();
		ph[i].l_f = i;
		ph[i].r_f = (i + 1) % total;
		ph[i].data = frk;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);	
}

int	ft_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (!str)
		return (-1);
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 10 + (str[i] - 48);
		else if (!(str[i] >= '0' && str[i] <= '9') || res > 2147483647)
			return (-1);
		i++;
	}
	return (res);
}

int	check_err(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) == -1)
		{
			printf ("your number is not integer or negative number\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

long	get_time()
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