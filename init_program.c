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

static int	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit(1);
	return (0);
}

static int	init_data(t_data *data, t_mlx *mlx)
{
	data->img = mlx_new_image(mlx->mlx_ptr, IMAGE_HEIGHT, IMAGE_HEIGHT);
	if (!data->img)
	{
		free(mlx->mlx_ptr);
		exit(1);
	}
	data->add = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	if (!data->add)
	{
		free(mlx->mlx_ptr);
		free(data->img);
		exit(1);
	}
	return (0);
}

void	init_frac(t_fractal *frac)
{
	frac->zoom = 1;
}

static void	init_vars(t_vars *vars, t_mlx *mlx, t_data *data, t_fractal *frac)
{
	vars->mlx = mlx;
	vars->data = data;
	vars->frac = frac;
}

void	init_structs(t_mlx *mlx, t_data *data, t_fractal *frac, t_vars *vars)
{
	init_mlx(mlx);
	init_data(data, mlx);
	init_frac(frac);
	init_vars(vars, mlx, data, frac);
	mlx->window = mlx_new_window(mlx->mlx_ptr, IMAGE_WIDTH,
			IMAGE_HEIGHT, "Fractol Program");
	if (!mlx->window)
	{
		free(mlx->mlx_ptr);
		free(data->img);
		free(data->add);
		exit(1);
	}
}
