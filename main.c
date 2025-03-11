#include "main.h"

void	my_put_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->add + y * img->line_length + x * img->bits_per_pixel / 8;
	*((unsigned int *)dst) = color;
}

// double	ft_abs(double d)
// {
// 	if (d < 0)
// 		d *= -1;
// 	return (d);
// }

void	iterate_set(t_fractal *frac, t_data *img, double Px, double Py)
{
	int		i;
	double	tmp;

	i = 0;
	frac->Zre = frac->Cx;
	frac->Zim = frac->Cy;
	while (i < 10000 && fabs(frac->Zre) <= 2 && fabs(frac->Zim) <= 2)
	{
		// printf("Zre: %f\n", frac->Zre);
		// printf("Zim: %f\n", frac->Zim);
		tmp = frac->Zre;
		frac->Zre = pow(frac->Zre, 2) - pow(frac->Zim, 2) + frac->Cx;
		frac->Zim = tmp * frac->Zim * 2 + frac->Cy;
		i++;
	}
	// printf("Zre: %f\n", frac->Zre);
	// printf("Zim: %f\n", frac->Zim);
	if (fabs(frac->Zre) <= 2 && fabs(frac->Zim) <= 2)
		my_put_pixel(img, Px, Py, 0x000000FF);
	else
		my_put_pixel(img, Px, Py, 0x00000000);
}

void	print_mandelbrot_to_window(t_fractal *frac, t_data *img)
{
	double	Px;
	double	Py;
	// int	iter_ret;

	Py = 0;
	while ((int)Py <= (int)frac->height)
	{
		Px = 0;
		while ((int)Px <= (int)frac->width)
		{
			frac->Cx = (Px * (double)4 / (double)frac->width) - (double)2;
			frac->Cy = (Py * (double)4 / (double)frac->height) - (double)2;
			printf("Cx: %f\n", frac->Cx);
			printf("Cy: %f\n", frac->Cy);
			iterate_set(frac, img, Px, Py);
			Px++;
		}
		Py++;
	}
}

int	mlx_play_around()
{
	void	*mlx_ptr;
	void	*window;
	t_data		img;
	t_fractal	frac;

	frac.height = 1080;
	frac.width = 1080;
	mlx_ptr = (void *)mlx_init();
//	if (!mlx_ptr)
//	return (1);
	window = mlx_new_window(mlx_ptr, frac.width, frac.height, "Playing around");
	//	if (!window)
//	return (1);
	img.img = mlx_new_image(mlx_ptr, frac.width, frac.height);
//	if (img.img == NULL)
//	{
//	mlx_destroy_window(mlx_ptr, window);
	// return (1);
	// }
	img.add = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
//	if (img.add == NULL)
//	{
//	mlx_destroy_window(img.img, window);
	//	mlx_destroy_window(mlx_ptr, window);
	//	free(img.img);
	//	return (1);
	//	}
	frac.Zre = 0;
	frac.Zim = 0;
	print_mandelbrot_to_window(&frac, &img);
	// fill_image_pattern(&img);
	mlx_put_image_to_window(mlx_ptr, window, img.img, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}

int main()
{
	mlx_play_around();
	return (0);
}
