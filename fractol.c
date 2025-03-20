/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:24:32 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/03/14 16:24:34 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char *av[])
{
	t_mlx		mlx;
	t_data		data;
	t_fractal	frac;
	t_vars		vars;

	handle_parsing(ac, av, &frac);
	init_structs(&mlx, &data, &frac, &vars);
	generate_fractal(&vars);
	mlx_hook(mlx.win_ptr, 17, 0, close_program, &vars);
	mlx_key_hook(mlx.win_ptr, key_hook, &vars);
	mlx_mouse_hook(mlx.win_ptr, mouse_hook, &vars);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
