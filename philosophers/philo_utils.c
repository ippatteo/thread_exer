/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevi il re, <capitano delle troie>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:12:00 by kevi il re,       #+#    #+#             */
/*   Updated: 2024/02/06 18:42:44 by kevi il re,      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*timer(void *ptr)
{
	u_int64_t	start;
	t_philo		*philo;
	
	philo = (t_philo *)ptr;
	while(philo->flag == 0)
	{
		ft_usleep(10);
		start += 10;
		if (start > (u_int64_t)philo->data->t_die)
			{
				philo->dead = 1;
				philo->flag = 1;
				philo->data->sms_flag = 1;
			}
	}
	return(NULL);
}

int	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void ft_eat(t_philo *philo, pthread_t delorian)
{
	
	if (pthread_mutex_lock(philo->fork_l) == 0)
	{
		sms(philo->data, "has taken a fork", philo->id_philo);
		pthread_mutex_lock(philo->fork_r);
	}
	pthread_join(delorian, NULL);
	// ricordare di unlockare
	sms(philo->data, "is eating", philo->id_philo);
	ft_usleep(philo->t_eat);
	pthread_create(&delorian, NULL, &timer, &philo);
	 philo->meal++;
	 if(philo->meal == philo->data->n_eat && philo->data->n_eat > 0)
			philo->sated = 1;
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	if (philo->dead == 1)
		return ;
	sms(philo->data, "sta dormendo", philo->id_philo);
	if (philo->t_sleep >= philo->t_die)
	{
		ft_usleep(philo->t_die - philo->t_sleep);
		philo->dead = 1;
	}
	else
		ft_usleep(philo->t_sleep);
}

void *ft_routine(void *ptr)
{
	t_philo *philo;
	pthread_t delorian;

	philo = (t_philo *)ptr;
	while (philo->dead == 0)
	{
		pthread_create(&delorian, NULL, &timer, &philo);
		ft_eat(philo, delorian);
		sms(philo->data, "is thinking", philo->id_philo); 
	}
	return (NULL);
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

void sms(t_data *data, char *str, int id)
{
	if(data->sms_flag == 0)
		printf("%ld philo n%d %s\n", (get_time() - data->time), id, str);
}