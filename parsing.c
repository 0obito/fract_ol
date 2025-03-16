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

void	print_error_and_exit(void)
{
	write(1, "There's been some error!\n", 25);
/*	write(1, "Wrong input. Here are the valid arguuments you can use:\n", 52);
	write(1, "Mandelbrot:\t`./fractol Mandelbrot`\n", 35);
	write(1, "Julia\t`./fractol Julia`\n", 24);*/
	exit(1);
}

int	ft_strcmp(char *s1, char *s2)
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

int	handle_parsing(int ac, char *av[])
{
	double	julia_x_input;
	double	julia_y_input;

	if (ac == 2 && (ft_strcmp("Mandelbrot", av[1]) == 0
			|| ft_strcmp("mandelbrot", av[1]) == 0))
		generate_fractal(0, JULIA_X, JULIA_Y);
	else if (ac == 2 && (ft_strcmp("Julia", av[1]) == 0
			|| ft_strcmp("julia", av[1]) == 0))
		generate_fractal(1, JULIA_X, JULIA_Y);
	else if (ac == 4 && (ft_strcmp("Julia", av[1]) == 0
			|| ft_strcmp("julia", av[1]) == 0))
	{
		julia_x_input = ft_atod(av[2]);
		julia_y_input = ft_atod(av[3]);
		generate_fractal(1, julia_x_input, julia_y_input);
	}
	else
		print_error_and_exit();
	return (0);
}
