/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevi il re, <capitano delle troie>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:40:26 by kevi il re,       #+#    #+#             */
/*   Updated: 2024/02/09 10:26:01 by kevi il re,      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int ft_kill_all(t_data *data, int i)
{
	if (data->philo[i].dead == 1)
	{
		pthread_mutex_lock(&data->lock);
		data->end = 1;
		pthread_mutex_unlock(&data->lock);
		sms(data, "is dead", data->philo[i].id_philo);
		return (1);
	}
	else
		return (0);
}

void *atac(void *ptr)
{
	t_data	*data;
	int		i;
	int 	a;
	
	data = (t_data *)ptr;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			if(data->philo[i].end_philo == 1)
			{
				if (ft_kill_all(data, i))
					return (NULL);
				if(data->philo[i].sated == 1)
				{
					a = 0;
					while (a < data->n_philo && data->philo[a].sated == 1)
						a++;
					if (a > data->n_philo)
						return (NULL);
				}
			}
			i++;
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	
	if (ac >= 5 && ac <= 6)
	{
		init(&data, ac, av);
		if (error(&data))
			return (0);
		alloc(&data);
		init_philos(&data);
		init_fork(&data);
		init_threads(&data);
		free_all(&data);
	}
	else
	{
		write(2, "Error\n", 6);
		return (0);
	}
}
