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

size_t	ft_sqrt(size_t len)
{
	size_t	result;

	if (len == 0 || len == 1)
		return (len);
	result = 1;
	while (result * result < len)
		result++;
	return (result);
}

void	my_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 1000 || y < 0 || y >= 1000)
		return ;
	dst = data->add + y * data->line_length + x * data->bits_per_pixel / 8;
	*((unsigned int *)dst) = color;
}


// Mandelbrot:
// c_x = scale(px);
// c_y = scale(py);
// z_re = scale(px);
// z_im = scale(py);

// Julia
// c_x = a;
// c_y = b;
// z_re = scale(px);
// z_im = scale(py);
// Zi+1 = Zi ^ 2 + C;


void	fill_pixel(int px, int py, int bin, t_vars *vars)
{
	int		i;
	double	tmp;
	int		color;

	vars->frac->z_re = (((double)px * ((double)COMPLEX_WIDTH / vars->frac->zoom) / (double)(IMAGE_WIDTH - 1)) - ((double)2 / vars->frac->zoom)) * bin + vars->frac->c_x;
	vars->frac->z_im = (((double)py * ((double)COMPLEX_HEIGHT / vars->frac->zoom) / (double)(IMAGE_HEIGHT - 1)) - ((double)2 / vars->frac->zoom)) * bin + vars->frac->c_y;
	i = 0;
	while(i < ITERATIONS_LIMIT && (vars->frac->z_re * vars->frac->z_re + vars->frac->z_im * vars->frac->z_im) <= 4)
	{
		tmp = vars->frac->z_re;
		vars->frac->z_re = (vars->frac->z_re * vars->frac->z_re) - (vars->frac->z_im * vars->frac->z_im) + vars->frac->c_x;
		vars->frac->z_im = tmp * vars->frac->z_im * 2 + vars->frac->c_y;
		i++;
	}
	if (i == ITERATIONS_LIMIT)
		my_put_pixel(vars->data, px, py, 0x00000000);
	else
	{
		color = ((i * 15) << 16) + ((i * 10) << 8) + (i * 5);
		// color = (int)(255 * ((double)sqrt(i) / (double)sqrt(ITERATIONS_LIMIT))) << 16; // Smooth Red Gradient
		my_put_pixel(vars->data, px, py, color);
	}
	// my_put_pixel(vars->data, px, py, color);
	vars->frac->c_x = 0;
	vars->frac->c_y = 0;
	vars->frac->z_re = 0;
	vars->frac->z_im = 0;
}

void	fill_image(t_vars *vars, int bin, double julia_x, double julia_y)
{
	int	px;
	int	py;

	py = 0;
	while (py < IMAGE_HEIGHT)
	{
		px = 0;
		while (px < IMAGE_WIDTH)
		{
			if (bin == 0)
			{
				vars->frac->c_x = ((double)px * ((double)COMPLEX_WIDTH / vars->frac->zoom) / (double)(IMAGE_WIDTH - 1)) - ((double)2 / vars->frac->zoom);
				vars->frac->c_y = ((double)py * ((double)COMPLEX_HEIGHT / vars->frac->zoom) / (double)(IMAGE_HEIGHT - 1)) - ((double)2 / vars->frac->zoom);
			}
			else
			{
				vars->frac->c_x = julia_x;
				vars->frac->c_y = julia_y;
			}
			fill_pixel(px, py, bin, vars);
			px++;
		}
		py++;
	}
}

// int	render(void *param)
// {
// 	t_vars	*vars;

// 	vars = param;
// 	// write(1, "Hello\n", 6);
// 	vars->frac->zoom *= 1.1;
// 	fill_image(vars);
// 	mlx_put_image_to_window(vars->mlx->mlx_ptr, vars->mlx->window, vars->data->img, 0, 0);
// 	return (0);
// }

int	generate_fractal(int bin, double julia_x, double julia_y)
{
	t_data		data;
	t_mlx		mlx;
	t_fractal	frac;
	t_vars		vars;

	// init_frac(zre, zim, cx, cy);
	init_structs(&mlx, &data, &frac, &vars);
	fill_image(&vars, bin, julia_x, julia_y);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.window, data.img, 0, 0);
	// mlx_loop_hook(mlx.mlx_ptr, render, &vars);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
