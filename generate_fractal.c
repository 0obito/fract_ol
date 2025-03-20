/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_fractal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:06:46 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/03/16 10:06:51 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	my_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 1000 || y < 0 || y >= 1000)
		return ;
	dst = data->add + y * data->line_length + x * data->bits_per_pixel / 8;
	*((unsigned int *)dst) = color;
}

static int	get_color(int i)
{
	static int	palette[96] = {
		0x180818, 0x200C24, 0x2B1333, 0x361940, 0x421F50, 0x4E2560,
		0x5A2D70, 0x663680, 0x723E90, 0x7F47A0, 0x8B50AF, 0x9761B7,
		0xA272BE, 0xAC84C5, 0xB696CB, 0xC0A8D1, 0xCABAD6, 0xD3C7D6,
		0xDACBD2, 0xE0CFCF, 0xE6D3CB, 0xEBD7C6, 0xF0DBC0, 0xF5DFB8,
		0xF8E3B0, 0xFCE7A8, 0xFFEAA0, 0xFFDF88, 0xFFC870, 0xFFA358,
		0xFF7D40, 0xFF5928, 0xFF3910, 0xF92308, 0xE71506, 0xD40A05,
		0xBF0505, 0xA70306, 0x8E0208, 0x74020B, 0x59030F, 0x3D0414,
		0x280519, 0x1A0621, 0x14082A, 0x0E0A32, 0x0C0C3A, 0x0A0E42,
		0x0A104A, 0x0A1252, 0x0B145A, 0x0E1762, 0x12196A, 0x181C72,
		0x1E1F7A, 0x252281, 0x2D2589, 0x36288F, 0x402C96, 0x4B2F9C,
		0x5633A2, 0x6236A8, 0x6E39AD, 0x7A3CB2, 0x873FB7, 0x9442BB,
		0xA045BF, 0xAC48C3, 0xB84BC6, 0xC44EC8, 0xD051CA, 0xDC54CB,
		0xE857CC, 0xF45ACC, 0xFF5DCB, 0xFF62C9, 0xFF68C6, 0xFF6DC2,
		0xFF72BD, 0xFF78B7, 0xFF7DB0, 0xFF83A8, 0xFF889F, 0xFF8E96,
		0xFF948C, 0xFF9982, 0xFF9F77, 0xFFA56B, 0xFFAA5F, 0xFFB053,
		0xFFB547, 0xFFBB3A, 0xFFC02D, 0xFFC51F, 0xFFCA11, 0xFFCF03
	};

	return (palette[i % 96]);
}

static void	fill_pixel(int px, int py, t_vars *vars)
{
	int		i;
	double	tmp;
	int		color;

	set_z_and_c(px, py, vars);
	i = 0;
	while (i < vars->frac->iterations && (vars->frac->z_re * vars->frac->z_re
			+ vars->frac->z_im * vars->frac->z_im) <= 4)
	{
		tmp = vars->frac->z_re;
		vars->frac->z_re = (vars->frac->z_re * vars->frac->z_re)
			- (vars->frac->z_im * vars->frac->z_im) + vars->frac->c_x;
		vars->frac->z_im = tmp * vars->frac->z_im * 2 + vars->frac->c_y;
		i++;
	}
	color = get_color(i);
	my_put_pixel(vars->data, px, py, color);
}

static void	fill_image(t_vars *vars)
{
	int	px;
	int	py;

	py = 0;
	while (py < IMG_HEI)
	{
		px = 0;
		while (px < IMG_WID)
		{
			vars->frac->c_x = vars->frac->julia_x;
			vars->frac->c_y = vars->frac->julia_y;
			if (vars->frac->mandelbrot == 1)
			{
				vars->frac->c_x = ((double)px * C_WID / (IMG_WID - 1) - (C_WID
							/ 2)) / vars->frac->zoom + vars->frac->shift_x;
				vars->frac->c_y = -1 * ((double)py * C_HEI / (IMG_HEI - 1) - (C_HEI
							/ 2)) / vars->frac->zoom + vars->frac->shift_y;
			}
			fill_pixel(px, py, vars);
			px++;
		}
		py++;
	}
}

int	generate_fractal(t_vars *vars)
{
	if (vars->frac->render == 1)
	{
		fill_image(vars);
		mlx_put_image_to_window(vars->mlx->mlx_ptr, vars->mlx->win_ptr,
			vars->data->img, 0, 0);
		vars->frac->render = 0;
	}
	return (0);
}
