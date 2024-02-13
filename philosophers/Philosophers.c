/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:40:26 by kevi il re,       #+#    #+#             */
/*   Updated: 2024/02/13 09:04:03 by mcamilli         ###   ########.fr       */
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
		pthread_mutex_lock(&data->print);
		sms(data, "is dead", data->philo[i].id_philo);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	else
	{
		return (0);
	}
		
}
int ft_sated(t_data *data, int i)
{
	int a;

	a = 0;
	if (data->philo[i].sated == 1)
	{
		while(a < data->n_philo)
		{
			if (data->philo[a].sated == 0)
				break ;
			a++;
		}
		if (a >= data->n_philo)
		{
			pthread_mutex_lock(&data->lock);
			data->end = 1;
			pthread_mutex_unlock(&data->lock);
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}


void *atac(void *ptr)
{
	t_data	*data;
	int i;
	
	data = (t_data *)ptr;
	while (data->end == 0)
	{	
		i = 0;
		while ( i <= data->n_philo -1)
		{
			if(ft_kill_all(data, i))
				return (NULL);
			if(ft_sated(data, i))
			{
				printf("ucito sated \n");
					return(NULL);
			}
			
		}
		i++;
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
