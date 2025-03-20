/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:06:03 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/03/14 16:07:33 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit(1);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, IMG_WID,
			IMG_HEI, "Fractol");
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
}

static void	init_data(t_data *data, t_mlx *mlx)
{
	data->img = mlx_new_image(mlx->mlx_ptr, IMG_HEI, IMG_HEI);
	if (!data->img)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
	data->add = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	if (!data->add)
	{
		mlx_destroy_image(mlx->mlx_ptr, data->img);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
}

static void	init_frac(t_fractal *frac)
{
	frac->iterations = 200;
	frac->shift_x = 0;
	frac->shift_y = 0;
	frac->render = 1;
	frac->zoom = 1;
}

void	init_structs(t_mlx *mlx, t_data *data, t_fractal *frac, t_vars *vars)
{
	init_mlx(mlx);
	init_data(data, mlx);
	init_frac(frac);
	vars->mlx = mlx;
	vars->data = data;
	vars->frac = frac;
}

void	set_z_and_c(int px, int py, t_vars *vars)
{
	double	z_x;
	double	z_y;

	if (vars->frac->mandelbrot == 1)
	{
		vars->frac->c_x = ((double)px * C_WID / (IMG_WID - 1) - (C_WID / 2))
			/ vars->frac->zoom + vars->frac->shift_x;
		vars->frac->c_y = ((double)py * C_HEI / (IMG_HEI - 1) - (C_HEI / 2))
			* -1 / vars->frac->zoom + vars->frac->shift_y;
		vars->frac->z_re = vars->frac->c_x;
		vars->frac->z_im = vars->frac->c_y;
	}
	if (vars->frac->julia == 1)
	{
		z_x = ((double)px * C_WID / (IMG_WID - 1) - (C_WID / 2))
			/ vars->frac->zoom + vars->frac->shift_x;
		z_y = ((double)py * C_HEI / (IMG_HEI - 1) - (C_HEI / 2))
			* -1 / vars->frac->zoom + vars->frac->shift_y;
		vars->frac->c_x = vars->frac->julia_x;
		vars->frac->c_y = vars->frac->julia_y;
		vars->frac->z_re = (z_x * z_x - z_y * z_y) + vars->frac->c_x;
		vars->frac->z_im = (2 * z_x * z_y) + vars->frac->c_y;
	}
}
