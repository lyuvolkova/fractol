#ifndef FRACTOL_H
# define FRACTOL_H
#include "stdio.h"
#include <math.h>
#define FRACTOL_UNKNOWN 0
#define FRACTOL_JULIA 1
#define FRACTOL_MALD 2
#define HEIGHT 768
#define WIDTH 1024
#define MAX_ITERATION 50

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_complex
{
    double re;
    double im;
}t_complex;

typedef struct s_fractol
{
    double min;
    double max;
    int iteration;
}t_fractol;

int	ft_strcmp(char *s1, char *s2);   
void paint_fractol(int type, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		iterate_mandelbrot(t_complex *c);

#endif