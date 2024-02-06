/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevi il re, <capitano delle troie>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:06:42 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/06 13:42:53 by kevi il re,      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <time.h>
#include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>
# include <pthread.h>
# include <stdlib.h>



typedef struct s_philo
{
	int	id_philo;	//numero filosofi
	int meal;
	int sated;
	int dead;
	int	t_die;	//time to die
	int	t_eat;	//time to eat
	int	t_sleep;	//time to sleep
	int	n_eat;
	pthread_mutex_t *fork_l; //how meny time they have to eat
	pthread_mutex_t *fork_r;
	t_data *data;
	
}	t_philo;

typedef struct s_data
{
	int	n_philo;	//numero filosofi
	int	t_die;	//time to die
	int	t_eat;	//time to eat
	int	t_sleep;	//time to sleep
	int	n_eat; //how meny time they have to eat
	t_philo *philo;
	pthread_mutex_t *forks;
	pthread_t *threads;
}	t_data;

void	init(t_data *data, int ac, char **av);
int		ft_atoi(char *str);
int		error(t_data *data);
int		ft_isdigit(int c);
void init_philos(t_data *data);
void init_fork(t_data *data);
void init_threads(t_data *data);
int	ft_usleep(uint64_t time);
void ft_eat(t_philo *philo);
void ft_thinking(t_philo *philo);
void *ft_routine(void *ptr);
void alloc(t_data *data);
uint64_t	get_time(void);

#endif
