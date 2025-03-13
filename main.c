#include "main.h"

void	my_put_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 1000 || y < 0 || y >= 1000)
		return ;
	dst = img->add + y * img->line_length + x * img->bits_per_pixel / 8;
	*((unsigned int *)dst) = color;
}

void	handle_no_event()
{
	return ;
}

void	iterate_set(t_fractal *frac, t_data *img, double Px, double Py)
{
	int		i;
	double	tmp;
	int		color;
	int		i_limit;

	i = 0;
	i_limit = 200;
	frac->Zre = frac->Cx;
	frac->Zim = frac->Cy;
	while (i < i_limit && (frac->Zre * frac->Zre + frac->Zim * frac->Zim) <= 4)
	{
		tmp = frac->Zre;
		frac->Zre = (frac->Zre * frac->Zre) - (frac->Zim * frac->Zim) + frac->Cx;
		frac->Zim = tmp * frac->Zim * 2 + frac->Cy;
		i++;
	}
	if (i == i_limit)
			color = 0x00000000;
	else
		color = (i * 15) << 16 | (i * 15) << 8 | (i * 3);
	my_put_pixel(img, Px, Py, color);
}

void	print_mandelbrot_to_window(t_fractal *frac, t_data *img, double zoom)
{
	double	Px;
	double	Py;

	Py = 0;
	while ((int)Py < (int)frac->height)
	{
		Px = 0;
		while ((int)Px < (int)frac->width)
		{
			// why does it not stop at Px \ Py = 999 since it starts from 0?
			// why does it not overflow or segfault when surpassing Px \ Py = 999?
			frac->Cx = (Px * ((double)4 / (double)zoom) / (double)(frac->width - 1)) - ((double)3 / (double)zoom);
			frac->Cy = (Py * ((double)4 / (double)zoom) / (double)(frac->height - 1)) - ((double)-3 / (double)zoom);
			// frac->Cx = ((Px * (double)4 / (double)frac->width) - (double)2) / (double)zoom;
			// frac->Cy = ((Py * (double)4 / (double)frac->height) - (double)2) / (double)zoom;
			iterate_set(frac, img, Px, Py);
			Px++;
		}
		Py++;
	}
}

int	zoom_effect(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	vars->zoom *= 1.005;
	print_mandelbrot_to_window(vars->frac, vars->img, vars->zoom);
	mlx_put_image_to_window(vars->frac->mlx_ptr, vars->frac->window, vars->img->img, 0, 0);
	if (vars->zoom >= 10)
		exit(0);
	return (0);
}

int	mlx_play_around()
{
	t_data		img;
	t_fractal	frac;
	t_vars		vars;

	frac.height = 500;
	frac.width = 500;
	frac.mlx_ptr = (void *)mlx_init();
	frac.window = mlx_new_window(frac.mlx_ptr, frac.width, frac.height, "Playing around");
	img.img = mlx_new_image(frac.mlx_ptr, frac.width, frac.height);
	img.add = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	frac.Zre = 0;
	frac.Zim = 0;
	vars.img = &img;
	vars.frac = &frac;
	vars.zoom = 1;
	print_mandelbrot_to_window(&frac, &img, vars.zoom);
	mlx_put_image_to_window(frac.mlx_ptr, frac.window, img.img, 0, 0);
	mlx_loop_hook(frac.mlx_ptr, zoom_effect, &vars);
	mlx_loop(frac.mlx_ptr);
	return (0);
}

int main()
{
	mlx_play_around();
	return (0);
}
