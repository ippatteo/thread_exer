/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevi il re, <capitano delle troie>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:40:26 by kevi il re,       #+#    #+#             */
/*   Updated: 2024/02/06 18:46:00 by kevi il re,      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_kill_all(t_data *data)
{
	int i;

	i = 0;
	write(1, "a\n", 2);
	data->sms_flag = 1;
	while (i < data->n_philo)
		data->philo[i++].dead = 1;
}

void *atac(void *ptr)
{
	t_data	*data;
	int		i;
	int		all_sated;
	
	data = (t_data *)ptr;
	while (1)
	{
		i = 0;
		all_sated = 0;
		while (i < data->n_philo)
		{
			if(data->philo[i].sated == 1)
				all_sated++;
			if(all_sated == data->n_philo || data->philo->dead == 1)
			{
				ft_kill_all(data);
				return (NULL);
			}
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	pthread_t pula;
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
		pthread_create(&pula, NULL, &atac, &data);
		pthread_join(pula, NULL);
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
