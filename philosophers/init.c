/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevi il re, <capitano delle troie>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:15:28 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/06 14:35:21 by kevi il re,      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init(t_data *data, int ac, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->n_eat = ft_atoi(av[5]);
	else
		data->n_eat = 0;
}

void init_philos(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].id_philo = i + 1;
		data->philo[i].t_die = data->t_die;
		data->philo[i].t_eat = data->t_eat;
		data->philo[i].t_sleep = data->t_sleep;
		data->philo[i].n_eat = data->n_eat;
		data->philo[i].meal = 0;
		data->philo[i].sated = 0;
		data->philo[i].dead = 0;
		data->philo[i].data = data;
		
		i++;
	}
}

void init_fork(t_data *data)
{
	int	i;
	
	i = 0;
	while(i++ < data->n_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philo[0].fork_l = &data->forks[0];
	data->philo[0].fork_r = &data->forks[data->n_philo - 1];
	i = 1;
	while (i < data->n_philo)
	{
		data->philo[i].fork_l = &data->forks[i];
		data->philo[i].fork_r = &data->forks[i - 1];
		i++;
	}
}

void init_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_create(&data->threads[i], NULL, &ft_routine, &data->philo[i]);
		i++;
		usleep(1000);//qui ritardi i filosofi
	}
}
