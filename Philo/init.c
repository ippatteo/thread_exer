/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:15:28 by mcamilli          #+#    #+#             */
/*   Updated: 2024/01/30 17:52:25 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init(t_var *var, int ac, char **av)
{
	var->np = ft_atoi(av[1]);
	var->td = ft_atoi(av[2]);
	var->te = ft_atoi(av[3]);
	var->ts = ft_atoi(av[4]);
	if (ac == 6)
		var->ts = ft_atoi(av[5]);
}
