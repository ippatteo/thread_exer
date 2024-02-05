/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matteocamilli <matteocamilli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:15:28 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/05 16:53:58 by matteocamil      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}
void ft_routine(void *ptr)
{
	t_philo *philo;
	int i;
	
	i = 1;
	philo = (t_philo *)ptr;
	 while(1)
	 {
		pthread_mutex_lock(&philo->fork_l);
		pthread_mutex_lock(&philo->fork_r);
		
	 }
	
}
int	ft_atoi(char *str)
{
	long int	r;
	int			s;
	int			i;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return(-1);	
		r = r * 10 + str[i++] - '0';
	}
	if (r > 2147483647 || r < -2147483647)
		return(-1);
	return (r * s);
}

int	error(t_data *data)
{
	if (data->n_philo < 0 || data->t_die < 0 || data->t_eat < 0 || data->t_sleep < 0 || data->n_eat < 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}


void alloc(t_data *data)
{
	int	i;
	
	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	data->threads = malloc(sizeof(pthread_t) * data->n_philo);
}

