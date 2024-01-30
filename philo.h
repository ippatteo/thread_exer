/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:06:42 by mcamilli          #+#    #+#             */
/*   Updated: 2024/01/30 18:06:37 by mcamilli         ###   ########.fr       */
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

typedef struct s_var
{
	int	np;	//numero filosofi
	int	td;	//time to die
	int	te;	//time to eat
	int	ts;	//time to sleep
	int	ea; //how meny time they have to eat
}	t_var;

void	init(t_var *var, int ac, char **av);
#endif
