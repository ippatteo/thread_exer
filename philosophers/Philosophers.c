/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matteocamilli <matteocamilli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:04:14 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/05 15:49:55 by matteocamil      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo *philo;

	if (ac >= 5 && ac <= 6)
	{
		init(&data, ac, av);
		if (error(&data))
			return (0);
		alloc(&data);
		init_philos(&data);
		init_forks(&data);
	}
	else
	{
		write(2, "Error\n", 6);
		return (0);
	}
		
}
