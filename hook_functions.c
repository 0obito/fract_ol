/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:34:00 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/03/19 02:34:04 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_mlx(t_vars *vars)
{
	if (vars->mlx->mlx_ptr)
	{
		if (vars->data->img)
			mlx_destroy_image(vars->mlx->mlx_ptr, vars->data->img);
		if (vars->mlx->win_ptr)
			mlx_destroy_window(vars->mlx->mlx_ptr, vars->mlx->win_ptr);
		mlx_destroy_display(vars->mlx->mlx_ptr);
		free(vars->mlx->mlx_ptr);
	}
}

int	close_program(t_vars *vars)
{
	free_mlx(vars);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	vars->frac->render = 1;
	if (keycode == XK_Escape)
		close_program(vars);
	else if (keycode == XK_equal)
		vars->frac->iterations += 20;
	else if (keycode == XK_minus)
		vars->frac->iterations += -20;
	else if (keycode == XK_Right)
		vars->frac->shift_x += 0.1 / vars->frac->zoom;
	else if (keycode == XK_Left)
		vars->frac->shift_x -= 0.1 / vars->frac->zoom;
	else if (keycode == XK_Down)
		vars->frac->shift_y -= 0.1 / vars->frac->zoom;
	else if (keycode == XK_Up)
		vars->frac->shift_y += 0.1 / vars->frac->zoom;
	else if (keycode == XK_r)
	{
		vars->frac->shift_x = 0;
		vars->frac->shift_y = 0;
	}
	else if (keycode == XK_F1)
	{
		vars->frac->shift_x *= 0.9;
		vars->frac->render = 0;
	}
	else if (keycode == XK_F2)
	{
		vars->frac->shift_x *= 1.1;
		vars->frac->render = 0;
	}
	else
		vars->frac->render = 0;
	if (vars->frac->render == 1)
		generate_fractal(vars);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	(void) x;
	(void) y;
	vars->frac->render = 1;
	if (keycode == 4)
		vars->frac->zoom *= 1.1;
	else if (keycode == 5)
		vars->frac->zoom *= 0.9;
	else if (keycode == 1)
		vars->frac->zoom = 1;
	else
		vars->frac->render = 0;
	if (vars->frac->render == 1)
		generate_fractal(vars);
	return (0);
}
