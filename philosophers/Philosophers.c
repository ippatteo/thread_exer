/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevi il re, <capitano delle troie>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:04:14 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/06 13:35:34 by kevi il re,      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	int i;

	i = 0;
	if (ac >= 5 && ac <= 6)
	{
		init(&data, ac, av);
		if (error(&data))
			return (0);
		alloc(&data);
		init_philos(&data);
		init_fork(&data);
		init_threads(&data);
		while(i < data.n_philo)
		{
			pthread_join(data.threads[i], NULL);
			i++;
		}
	}
	else
	{
		write(2, "Error\n", 6);
		return (0);
	}
		
}
