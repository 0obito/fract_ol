/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:22:08 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/03/14 16:22:11 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <X11/keysym.h>

# define IMG_WID 1000
# define IMG_HEI 1000
# define C_WID 4
# define C_HEI 4

typedef struct s_data
{
	void	*img;
	char	*add;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

typedef struct s_fractal
{
	int		julia;
	int		mandelbrot;
	double	c_x;
	double	c_y;
	double	z_re;
	double	z_im;
	double	julia_x;
	double	julia_y;
	int		iterations;
	double	shift_x;
	double	shift_y;
	double	render;
	// double	color_param;
	double	zoom;
}				t_fractal;

typedef struct s_vars
{
	t_data		*data;
	t_mlx		*mlx;
	t_fractal	*frac;
}				t_vars;

void	init_structs(t_mlx *mlx, t_data *data, t_fractal *frac, t_vars *vars);
void	handle_parsing(int ac, char *av[], t_fractal *frac);
double	ft_atod(char *s);
void	print_message_and_exit(void);
int		generate_fractal(t_vars *vars);
void	set_z_and_c(int px, int py, t_vars *vars);
int		close_program(t_vars *vars);
int		key_hook(int keycode, t_vars *vars);
int		mouse_hook(int keycode, int x, int y, t_vars *vars);

#endif /* MAIN_H */
