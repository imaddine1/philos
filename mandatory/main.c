/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:29:52 by iharile           #+#    #+#             */
/*   Updated: 2022/08/27 12:57:03 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_usleep(long duration)
{
	long	start;

	start = get_time();
	while (get_time() - start < duration)
		usleep(250);
}

void	*routine(void	*arg)
{
	t_philos	*ph;

	ph = (t_philos*)arg;
	if (ph->name % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		eat(ph);
		sleep_n_think(ph);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philos	*ph;
	t_data		frk;

	if (ac < 5 || ac > 6 || check_err(av))
	{
		printf ("you need to check all your parameters\n");
		return (0);
	}
	ph = malloc(sizeof(t_philos) * ft_atoi(av[1]));
	if (!ph)
	{
		printf ("malloc is failed\n");	
		return (0);
	}
	// initializing the data here
	initialize_data(ph, &frk, av);
	// read the data
	int i = -1;
	while (i < ft_atoi(av[1]))
	{
		pthread_create(ph[i].philos, NULL, &routine, &ph[i]);
		ft_usleep(1);
	}
	return (0);
}