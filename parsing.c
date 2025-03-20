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
	write(1, "\n\033[1;31mError:\033[0m Invalid arguments!\n", 38);
	write(1, "\n\033[1;34mUsage:\033[0m ./fractol [Set_Name] [X] [Y]\n", 48);
	write(1, "\n\033[1;32mSet_Name:\033[0m 'Mandelbrot' or 'Julia'\n", 46);
	write(1, "\033[1;32mX and Y:\033[0m Only for 'Julia' (optional)\n", 48);
	write(1, "\n\033[1;34mExamples:\033[0m\n", 22);
	write(1, "  ➤ ./fractol Mandelbrot\n", 27);
	write(1, "  ➤ ./fractol Julia 0.285 0.01\n\n", 34);
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
	else if ((ft_strcmp("Julia", av[1]) == 0
			|| ft_strcmp("julia", av[1]) == 0)
		&& (ac == 2 || ac == 4))
	{
		frac->mandelbrot = 0;
		frac->julia = 1;
		frac->julia_x = -0.79;
		frac->julia_y = 0.15;
		if (ac == 4)
		{
			frac->julia_x = ft_atod(av[2]);
			frac->julia_y = ft_atod(av[3]);
		}
	}
	else
		print_message_and_exit();
}
