/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:15:28 by mcamilli          #+#    #+#             */
/*   Updated: 2024/01/30 17:13:26 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *str, t_stack *stack)
{
	long int	r;
	int			s;
	int			i;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i++] == '-')
	{
		stack->error = 1;
		s = -1;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			stack->error = 1;
		r = r * 10 + str[i++] - '0';
	}
	if (r > 2147483647 || r < -2147483647)
		stack->error = 1;
	return (r * s);
}

int	error(t_var *var)
{
	if (stack->error == 1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	else
		return (0);
}
