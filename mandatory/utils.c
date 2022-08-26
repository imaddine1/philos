/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:34:55 by iharile           #+#    #+#             */
/*   Updated: 2022/08/26 18:03:53 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	initialize_data(t_philos *ph, t_data *frk, char **av)
{
	int	i;

	i = 0;
	frk->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[0]));
	ph = malloc(sizeof(t_philos) * ft_atoi(av[0]));
	if (!frk->forks || !ph)
	{
		printf ("malloc is failed\n");
		if (ph)
			free (ph);
		else if (frk->forks)
			free (frk->forks);
		return (NULL);
	}
	frk->time_die = ft_atoi(av[2]);
	frk->time_eat = ft_atoi(av[3]);
	frk->time_sleep = ft_atoi(av[4]);
	while (i < ft_atoi(av[0]))
	{
		pthread_mutex_init(&frk->forks[i], NULL);
		i++;
	}
	
	while (i < ft_atoi(av[0]))
	{
		i++;
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

	i = 0;
	while (av[i])
	{
		if (ft_atoi(av[i]) == -1)
		{
			printf ("your number is not integer\n");
			return (-1);
		}
		i++;
	}
	return (0);
}
