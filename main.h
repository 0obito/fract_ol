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
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>

# define IMAGE_WIDTH 800
# define IMAGE_HEIGHT 800

# define COMPLEX_WIDTH 4
# define COMPLEX_HEIGHT 4

# define ITERATIONS_LIMIT 10000

# define JULIA_X 0.355534
# define JULIA_Y -0.337292

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
	void	*window;
}				t_mlx;

typedef struct s_fractal
{
	double	c_x;
	double	c_y;
	double	z_re;
	double	z_im;
	double	zoom;
}				t_fractal;

typedef struct s_vars
{
	t_data		*data;
	t_mlx		*mlx;
	t_fractal	*frac;
}				t_vars;

void	init_structs(t_mlx *mlx, t_data *data, t_fractal *frac, t_vars *vars);
int	handle_parsing(int ac, char *av[]);
int	generate_fractal(int bin, double julia_x, double julia_y);
double	ft_atod(char *s);
void	print_error_and_exit(void);

#endif /* MAIN_H */
