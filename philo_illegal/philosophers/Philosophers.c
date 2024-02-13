/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:40:26 by kevi il re,       #+#    #+#             */
/*   Updated: 2024/02/13 12:42:29 by mcamilli         ###   ########.fr       */
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
	{
		return (0);
	}
}

void *atac(void *ptr)
{
	t_data	*data;
	int i;

	data = (t_data *)ptr;

	while (data->end == 0 && data->n_eat > 0)
	{
		i = 0;
		while (i < data->n_philo)
		{
			if(data->philo[i].sated == 0)
				break ;
			i++;
		}
		if (i >= data->n_philo)
		{
			pthread_mutex_lock(&data->lock);
			data->end = 1;
			printf("all sated\n");
			pthread_mutex_unlock(&data->lock);
			return (NULL);
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
