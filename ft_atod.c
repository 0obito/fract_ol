/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 07:49:11 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/03/16 07:50:30 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	skip_spaces(char **s)
{
	while (**s == ' ')
		(*s)++;
}

static double	ft_atod_fraction(char **s)
{
	int		i;
	double	fraction;
	double	divisor;

	(*s)++;
	fraction = 0;
	divisor = 1;
	i = 0;
	while (**s >= '0' && **s <= '9')
	{
		fraction = fraction * 10 + (**s - '0');
		divisor *= 10;
		(*s)++;
	}
	return ((double)(fraction / divisor));
}

double	ft_atod(char *s)
{
	int		sign;
	double	res;

	sign = 1;
	res = 0;
	skip_spaces(&s);
	if (*s == '-' || *s == '+')
		if (*(s++) == '-')
			sign = -1;
	if (*s < '0' || *s > '9')
		print_error_and_exit();
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		if (res > (double)2)
			print_error_and_exit();
		s++;
	}
	if (*s == '.')
		res += ft_atod_fraction(&s);
	skip_spaces(&s);
	if (*s)
		print_error_and_exit();
	return (res * sign);
}
