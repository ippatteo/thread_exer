/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:15:28 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/13 08:56:35 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void	init(t_data *data, int ac, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->time = get_time();
	pthread_mutex_init(&data->print, NULL);
	data->sms_flag = 0;
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
		data->philo[i].end_philo = 0;
		data->philo[i].is_eating = 0;
		data->philo[i].time_to_die = get_time() + data->t_die;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].lock_dead, NULL);
		i++;
	}
}

void init_fork(t_data *data)
{
	int	i;
	
	i = 0;
	while(i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
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
	pthread_t pula;
	int i;
	data->sated_condition = 0;
	data->end = 0;
	i = 0;
	pthread_mutex_init(&data->lock, NULL);
	pthread_create(&pula, NULL, &atac, data);
	while (i < data->n_philo)
	{
		pthread_create(&data->threads[i], NULL, &ft_routine, &data->philo[i]);
		pthread_detach(data->threads[i]);
		i++;
		usleep(1000);
		//qui ritardi i filosofi
	}
	pthread_join(pula, NULL);
}