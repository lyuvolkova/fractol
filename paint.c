/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:16:41 by qgrodd            #+#    #+#             */
/*   Updated: 2022/01/30 20:36:47 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int get_color(int i, int iteration_count, int shift)
{
	double t;
	int red, green, blue;
	t = (double)i/(double)iteration_count;
	if (shift > 2)
	{
		red = (int)((0+shift)%3 + 1) *(9 * (1 - t) * pow(t, 3) * 255);
		green = (int)((1+shift)%3 + 1)*(15 * pow((1 - t), 2) * pow(t, 2) * 250);
		blue = (int)((2+shift)%3 + 1)*(8.5 * pow((1 - t), 3) * t * 25);
		
	}
	else if (shift == 1)
	{
		green = (int)((0+shift)%3 + 1) *(9 * (1 - t) * pow(t, 3) * 200);
		blue = (int)((0+shift)%3 + 1) *(15 * pow((1 - t), 2) * pow(t, 2) * 25);
		red = (int)((0+shift)%3 + 1) *(8.5 * pow((1 - t), 3) * t * 100);
		
	}
	else if (shift == 2)
	{
		blue = (int)(9 * (1 - t) * pow(t, 3) * 255);
		red = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
		green = (int)(8.5 * pow((1 - t), 3) * t * 255);
		
	}
	else{
		red = (int)(9 * (1 - t) * pow(t, 3) * 255);
		green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
		blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
	}
	return (red << 16 | green << 8 | blue);
}

int iterate_julia(t_fractol *fr)
{
	int			i;
	t_complex	z;

	i = 0;
	
	z = init_complex(fr->c.re, fr->c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && i < MAX_ITERATION)
	{
		z = init_complex(
			pow(z.re, 2.0) - pow(z.im, 2.0) + fr->k.re,
			2.0 * z.re * z.im + fr->k.im);
			i++;
	}
	return(i);

}

void init_min_max(t_fractol *fr)
{
	fr->ofst.y = (HEIGHT - WIDTH) / 2;
	fr->ofst.x  = 0;
	fr->size = WIDTH;
	if (fr->size > HEIGHT) {
		fr->size  = HEIGHT;
		fr->ofst.x = (WIDTH - HEIGHT) / 2;
		fr->ofst.y = 0;
	}
	//fr->factor = 4.0 / (double)fr->size;
}

void julia(t_fractol *fr, int iteration_count)
{
	int i;
	int y, x;
	
	//init_min_max(fr);
	fr->ofst.y = 0;
	fr->ofst.x  = 0;
	fr->size = WIDTH;
	fr->factor = init_complex((fr->max.re - fr->min.re) /WIDTH, (fr->max.im - fr->min.im)/HEIGHT);

	y = 0;
	while(y < fr->size)
	{
		fr->c.im = fr->max.im - y * fr->factor.im;
		x = 0;
		while (x < fr->size)
		{
			fr->c.re = fr->min.re + x * fr->factor.re;
			i = iterate_julia(fr);
			my_mlx_pixel_put(&fr->img, x + fr->ofst.x, y + fr->ofst.y, get_color(i, iteration_count, fr->color_sh));
			x++;
		}
		y++; 
	}
	mlx_put_image_to_window(fr->mlx, fr->mlx_win, fr->img.img, 0 , 0);
}

void mandelbrot(t_fractol *fr, int iteration_count)
{
	int i;
	int y, x;
	//t_fractol fr;
	
	//init_min_max(fr);
	fr->ofst.y = 0;
	fr->ofst.x  = 0;
	fr->size = WIDTH;
	fr->factor = init_complex((fr->max.re - fr->min.re) /WIDTH, (fr->max.im - fr->min.im)/HEIGHT);
	y = 0;
	while(y < fr->size)
	{
		fr->c.im = fr->max.im - y * fr->factor.im;
		x = 0;
		while (x < fr->size)
		{
			fr->c.re = fr->min.re + x * fr->factor.re;
			i = iterate_mandelbrot(&fr->c);
			my_mlx_pixel_put(&fr->img, x + fr->ofst.x, y + fr->ofst.y, get_color(i, iteration_count, fr->color_sh));
			x++; 
		}
		y++; 
	}
	mlx_put_image_to_window(fr->mlx, fr->mlx_win, fr->img.img, 0 , 0);
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


int paint_fractol(t_fractol *fr)
{
	if (!fr->is_need_render) {
		return (0);
	}

	if(FRACTOL_JULIA == fr->type)
	{
		
		julia(fr, MAX_ITERATION);
		
		//my_mlx_pixel_put(img, 5, 5, 0x00FF0000);
		//fill_rectangle(img,5,5,40,100, 0x00FF0000);
		
		//mlx_mouse_hook(img->img, mouse_reaction_click, (void*)&img);

	}
	else if(FRACTOL_MALD == fr->type)
	{
		//my_mlx_pixel_put(img, 5, 5, 0x000000FF);
		mandelbrot(fr, MAX_ITERATION);
	}

	fr->is_need_render = 0;

	return(0);

}