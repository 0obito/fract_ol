/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:35:19 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/03/14 16:35:22 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_message_and_exit(void)
{
	write(1, "Usage: ./fract-ol [Set_Name] [X] [Y]\n", 37);
	write(1, "Set_Name: 'Mandelbrot' or 'Julia' (required)\n", 45);
	write(1, "X and Y: Only for 'Julia' (optional, defaults will be used if not provided)\n", 76);
	write(1, "Example:\n", 9);
	write(1, "  ./fract-ol Mandelbrot\n", 24);
	write(1, "  ./fract-ol Julia 0.285 0.01\n", 30);
	exit(1);
}

static int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}

void	handle_parsing(int ac, char *av[], t_fractal *frac)
{
	if (ac == 2 && (ft_strcmp("Mandelbrot", av[1]) == 0
			|| ft_strcmp("mandelbrot", av[1]) == 0))
	{
		frac->mandelbrot = 1;
		frac->julia = 0;
		frac->julia_x = 0;
		frac->julia_y = 0;
	}
	else if (ac == 2 && (ft_strcmp("Julia", av[1]) == 0
			|| ft_strcmp("julia", av[1]) == 0))
	{
		frac->mandelbrot = 0;
		frac->julia = 1;
		frac->julia_x = -0.79;
		frac->julia_y = 0.15;
	}
	else if (ac == 4 && (ft_strcmp("Julia", av[1]) == 0
			|| ft_strcmp("julia", av[1]) == 0))
	{
		frac->mandelbrot = 0;
		frac->julia = 1;
		frac->julia_x = ft_atod(av[2]);
		frac->julia_y = ft_atod(av[3]);
	}
	else
		print_message_and_exit();
}
