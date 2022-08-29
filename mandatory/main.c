/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:29:52 by iharile           #+#    #+#             */
/*   Updated: 2022/08/29 17:24:11 by iharile          ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_philos	*ph;
	t_data		frk;
	int			i;

	if (ac < 5 || ac > 6 || check_err(av))
	{
		printf ("you need to check all your parameters\n");
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
	if (death_n_meals(ph, ft_atoi(av[1])) == 1)
		return (0);
}