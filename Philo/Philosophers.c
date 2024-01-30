/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:04:14 by mcamilli          #+#    #+#             */
/*   Updated: 2024/01/30 18:06:44 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_var	var;

	if (ac >= 5 && ac <= 6)
	{
		init(&var, ac, av);
		if (error(&var))
			return (0);
	}
	else
		return (0);
}
