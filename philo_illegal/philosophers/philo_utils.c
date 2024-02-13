/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:12:00 by kevi il re,       #+#    #+#             */
/*   Updated: 2024/02/13 14:38:34 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*timer(void *ptr)
{
	t_philo		*philo;
	philo = (t_philo *)ptr;
	while(philo->data->end == 0)
	{

		if (get_time() >= philo->time_to_die && !philo->is_eating)
		{
			pthread_mutex_lock(&philo->data->lock);
			pthread_mutex_lock(&philo->data->print);
			sms(philo->data, "is dead", philo->id_philo);
			philo->data->end = 1;
			pthread_mutex_unlock(&philo->data->print);
			pthread_mutex_unlock(&philo->data->lock);

			return(NULL);
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

void ft_eat(t_philo *philo) //void ft_eat(t_philo *philo, pthread_t delorian)
{
	pthread_mutex_lock(philo->fork_l);
	pthread_mutex_lock(&philo->data->print);
	sms(philo->data, "has taken a fork", philo->id_philo);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(philo->fork_r);
	pthread_mutex_lock(&philo->data->print);
	sms(philo->data, "has taken a fork", philo->id_philo);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->lock_dead);
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->lock_dead);
	pthread_mutex_lock(&philo->data->print);
	sms(philo->data, "is eating", philo->id_philo);
	pthread_mutex_unlock(&philo->data->print);
	ft_usleep(philo->t_eat);
	pthread_mutex_lock(&philo->lock_dead);
	philo->time_to_die = get_time() + (uint64_t)philo->data->t_die;
	philo->meal++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->lock_dead);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

int ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	sms(philo->data, "is sleeping", philo->id_philo);
	pthread_mutex_unlock(&philo->data->print);
	ft_usleep(philo->t_sleep);
	return (0);
}

void is_it_sated(t_philo *philo)
{
	 if(philo->meal >= philo->data->n_eat && philo->data->n_eat > 0)
		 {
			pthread_mutex_lock(&philo->lock_dead);
			philo->sated = 1;
			pthread_mutex_unlock(&philo->lock_dead);
		 }
}
void *ft_routine(void *ptr)
{
	t_philo *philo;
	pthread_t delorian;

	philo = (t_philo *)ptr;
	if (pthread_create(&delorian, NULL, &timer, (void *)philo))
		return (NULL);
	while (philo->data->end == 0)
	{
		ft_eat(philo);
		is_it_sated(philo);
		//ft_eat(philo,delorian);
		if (philo->data->end == 1)
			break ;
		ft_sleeping(philo);
		if (philo->data->end == 1)
			break ;
		pthread_mutex_unlock(&philo->data->print);
		sms(philo->data, "is thinking", philo->id_philo);
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_join(delorian, NULL);
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
	printf("end = %d  id = %d\n", data->end, id);
	if(data->end == 1)
		return ;
	printf("%llu philo n%d %s, end = %d\n", (get_time() - data->time), id, str, data->end);

}

void free_all(t_data *data)
{	int i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(data->philo[i].fork_l);
		pthread_mutex_destroy(data->philo[i].fork_r);
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].lock_dead);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->print);
	free(data->philo);
	free(data->forks);
	free(data->threads);
}
