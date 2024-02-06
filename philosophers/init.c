/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matteocamilli <matteocamilli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:15:28 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/05 17:45:33 by matteocamil      ###   ########.fr       */
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
}

void init_philos(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->n_philo)
	{
		data->philo->id_philo = i + 1;
		data->philo->t_die = data->t_die;
		data->philo->t_eat = data->t_eat;
		data->philo->t_sleep = data->t_sleep;
		data->philo->n_eat = data->n_eat;
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
		pthread_create(data->threads[i], NULL, ft_routine(), &data->philo[i]);
		i++;
	}
}
