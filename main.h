#ifndef MAIN_H
# define MAIN_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct	s_data {
	void	*img;
	char    *add;
	int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_data;

typedef struct  s_fractal {
    size_t  height;
    size_t  width;
    double  Cx;
    double  Cy;
    double  Zre;
    double  Zim;
}               t_fractal;

int mlx_play_around();

#endif /* MAIN_H */
