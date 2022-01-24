#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void fill_rectangle(t_data *img,  int x, int y, int width, int heigth, int color)
{
    int i;
    int j;

    
    j = y + heigth;

    while (y < j)
    {
        i = x + width;
        while(x < i)
        {
            my_mlx_pixel_put(img, i, j, color); 
            i--;    
        }
        j--;
    }

}
t_complex init_complex(double re, double im)
{
    t_complex complex;
    
    complex.re = re;
    complex.im = im;
    return (complex);
}

int get_color(int i, int iteration_count)
{
    double t;
    int red, green, blue;
    
    t = (double)i/(double)iteration_count;
    red = (int)(9 * (1 - t) * pow(t, 3) * 255);
    green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
    blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
    return (red << 16 | green << 8 | blue);
}

void mandelbrot(t_data *img, int iteration_count)
{
    int i;
    int y, x;
    t_complex z, c;
    t_complex factor;
    t_complex min;
    t_complex max;
    int width, height;

    width = WIDTH;
    height = HEIGHT;

    min.re = -2.0;
    max.re = 2.0;
    min.im = -2.0;
    max.im = min.im + (max.re - min.re) * height / width;
    factor.re = (max.re - min.re) / (width - 1);
    factor.im = (max.im - min.im) / (height - 1);
    y=0;
    while(y < height)
    {
        c.im = max.im - y * factor.im;
        x = 0;
        while (x < width)
        {
            c.re = min.re + x * factor.re;
            z = init_complex(c.re, c.im);
            i = iterate_mandelbrot(&c);
            my_mlx_pixel_put(img, x, y, get_color(i, iteration_count));
            x++;
        }
        y++; 
    }
}

int		iterate_mandelbrot(t_complex *c)
{
	int			iteration;
	t_complex	z;

	iteration = 0;
	z = init_complex(c->re, c->im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
		&& iteration < MAX_ITERATION)
	{
		z = init_complex(
			pow(z.re, 2.0) - pow(z.im, 2.0) + c->re,
			2.0 * z.re * z.im + c->im);
		iteration++;
	}
	return (iteration);
}

void paint_fractol(int type, t_data *img)
{
    
    if(FRACTOL_JULIA == type)
    {
        //my_mlx_pixel_put(img, 5, 5, 0x00FF0000);
        fill_rectangle(img,5,5,40,100, 0x00FF0000);

    }
    else if(FRACTOL_MALD == type)
    {
        //my_mlx_pixel_put(img, 5, 5, 0x000000FF);
        mandelbrot(img, 50);
    }

}