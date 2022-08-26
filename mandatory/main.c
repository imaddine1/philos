/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:29:52 by iharile           #+#    #+#             */
/*   Updated: 2022/08/26 17:51:29 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"



int	main(int ac, char **av)
{
	t_philos	*ph;
	t_fork		frk;

	if (ac < 5 || ac > 6 || check_err(av))
	{
		printf ("you need to check all your parameters\n");
		return (0);
	}
	
	initialize_data(ph, &frk, av);
	return (0);
}