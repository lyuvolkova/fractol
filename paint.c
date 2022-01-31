/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:16:41 by qgrodd            #+#    #+#             */
/*   Updated: 2022/02/01 01:07:36 by lubov            ###   ########.fr       */
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
	if (shift > 1)
	{
		green = (int)((0 + shift)%3 + 1) *(9 * (1 - t) * t * t * t * 255);
		blue = (int)((1 + shift)%3 + 1)*(15 * (1 - t) * (1 - t) * t * t * 255);
		red = (int)((2 + shift)%3 + 1)*(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	else if (shift == 1)
	{
		blue = (int)(9 * (1 - t) * t * t * t * 255);
		red = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		green = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);	
	}
	else{
		red = (int)(9 * (1 - t) * t * t * t * 255);
		green = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	return (red << 16 | green << 8 | blue);
}

int iterate_julia(t_fractol *fr)
{
	int			i;
	t_complex	z;

	i = 0;
	
	z = init_complex(fr->c.re, fr->c.im);
	while (z.re * z.re + z.im * z.im <= 4 && i < fr->max_iter)
	{
		z = init_complex(
			z.re * z.re - z.im * z.im + fr->k.re,
			2.0 * z.re * z.im + fr->k.im);
			i++;
	}
	return(i);

}

void init_offset(t_fractol *fr)
{
	fr->ofst.y = (HEIGHT - WIDTH) / 2;
	fr->ofst.x  = 0;
	fr->size = WIDTH;
	if (fr->size > HEIGHT) {
		fr->size = HEIGHT;
		fr->ofst.x = (WIDTH - HEIGHT) / 2;
		fr->ofst.y = 0;
	}

	fr->factor = init_complex(
		(fr->max.re - fr->min.re) / WIDTH,
		(fr->max.im - fr->min.im) / HEIGHT
	);
}

void julia(t_fractol *fr)
{
	int i;
	int y, x;
	
	init_offset(fr);

	y = 0;
	while(y < fr->size)
	{
		fr->c.im = fr->max.im - y * fr->factor.im;
		x = 0;
		while (x < fr->size)
		{
			fr->c.re = fr->min.re + x * fr->factor.re;
			i = iterate_julia(fr);
			my_mlx_pixel_put(&fr->img, x + fr->ofst.x, y + fr->ofst.y, get_color(i, fr->max_iter, fr->color_sh));
			x++;
		}
		y++; 
	}
	mlx_put_image_to_window(fr->mlx, fr->mlx_win, fr->img.img, 0 , 0);
}

void mandelbrot(t_fractol *fr)
{
	int i;
	int y;
	int x;

	init_offset(fr);
	
	x = 0;
	y = 0;
	fr->c.im = fr->max.im - y * fr->factor.im;
	while(y < fr->size)
	{
		if (x < fr->size) {
			fr->c.re = fr->min.re + x * fr->factor.re;
			i = iterate_mandelbrot(&fr->c, fr->max_iter);
			my_mlx_pixel_put(&fr->img, x + fr->ofst.x, y + fr->ofst.y, get_color(i, fr->max_iter, fr->color_sh));
			x++;
			continue;
		}
		
		x = 0;
		y++;
		fr->c.im = fr->max.im - y * fr->factor.im;
	}
	mlx_put_image_to_window(fr->mlx, fr->mlx_win, fr->img.img, 0 , 0);
}

int		iterate_mandelbrot(t_complex *c, int max_iteration)
{
	int			iteration;
	t_complex	z;
	double p;
	double p0;
	
	p = sqrt((c->re - 1 / 4) * (c->re - 1 / 4) + c->im * c->im);
	p0 = 1 / 2 - 1 / 2 * cos( atan2(c->im, c->re - 1 / 4));
	if (p <= p0){
		return max_iteration;
	}
	
	iteration = 0;
	z = init_complex(c->re, c->im);
	while (z.re * z.re + z.im * z.im <= 4
		&& iteration < max_iteration)
	{
		z = init_complex(
			z.re * z.re - z.im * z.im + c->re,
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
		
		julia(fr);
		
		//my_mlx_pixel_put(img, 5, 5, 0x00FF0000);
		//fill_rectangle(img,5,5,40,100, 0x00FF0000);
		
		//mlx_mouse_hook(img->img, mouse_reaction_click, (void*)&img);

	}
	else if(FRACTOL_MALD == fr->type)
	{
		//my_mlx_pixel_put(img, 5, 5, 0x000000FF);
		mandelbrot(fr);
	}

	fr->is_need_render = 0;

	return(0);

}