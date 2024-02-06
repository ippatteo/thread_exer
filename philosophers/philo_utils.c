/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevi il re, <capitano delle troie>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:12:00 by kevi il re,       #+#    #+#             */
/*   Updated: 2024/02/06 13:44:26 by kevi il re,      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int ft_usleep(uint64_t time)
{
	uint64_t start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void ft_eat(t_philo *philo)
{
	printf("philo n %d ha preso la forchetta\n", philo->id_philo);
	if (pthread_mutex_lock(philo->fork_l) == 0)
		pthread_mutex_lock(philo->fork_r);
	// ricordare di unlockare
	printf("philo n %d sta mangiando\n", philo->id_philo);
	ft_usleep(philo->t_eat);
	 philo->meal++
	 if(philo->meal = philo->data->n_eat && philo->data->n_eat > 0)
		philo->sated = 1;
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	printf("philo n %d sta dormendo\n", philo->id_philo);
	ft_usleep(philo->t_sleep);
}

void ft_thinking(t_philo *philo)
{
	printf("philo n %d sta pensando\n", philo->id_philo);
}
void *ft_routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		//printf("sono il filo %d\n", philo->id_philo);
		ft_eat(philo);
		ft_thinking(philo);
	}
}
int ft_atoi(char *str)
{
	long int r;
	int s;
	int i;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		r = r * 10 + str[i++] - '0';
	}
	if (r > 2147483647 || r < -2147483647)
		return (-1);
	return (r * s);
}

int error(t_data *data)
{
	if (data->n_philo < 0 || data->t_die < 0 || data->t_eat < 0 || data->t_sleep < 0 || data->n_eat < 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	else
		return (0);
}

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void alloc(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	data->threads = malloc(sizeof(pthread_t) * data->n_philo);
}

uint64_t get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}