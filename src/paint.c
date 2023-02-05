/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:16:41 by qgrodd            #+#    #+#             */
/*   Updated: 2022/02/02 01:52:04 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	iterate_julia(t_fractol *fr)
{
	int			i;
	t_complex	z;

	i = 0;
	z = init_complex(fr->c.re, fr->c.im);
	while (z.re * z.re + z.im * z.im <= 4 && i < fr->max_iter)
	{
		z = init_complex(\
			z.re * z.re - z.im * z.im + fr->k.re, \
			2.0 * z.re * z.im + fr->k.im);
			i++;
	}
	return (i);
}

void	julia(t_fractol *fr)
{
	int	i;
	int	y;
	int	x;

	y = 0;
	fr->factor = init_complex(\
		(fr->max.re - fr->min.re) / WIDTH, \
		(fr->max.im - fr->min.im) / HEIGHT);
	while (y < fr->size)
	{
		fr->c.im = fr->max.im - y * fr->factor.im;
		x = 0;
		while (x < fr->size)
		{
			fr->c.re = fr->min.re + x * fr->factor.re;
			i = iterate_julia(fr);
			my_mlx_pixel_put(&fr->img, x, y, get_color(i, \
			fr->max_iter, fr->color_sh));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fr->mlx, fr->mlx_win, fr->img.img, 0, 0);
}

void	mandelbrot(t_fractol *fr)
{
	int	i;
	int	y;
	int	x;

	y = 0;
	fr->factor = init_complex(\
		(fr->max.re - fr->min.re) / WIDTH, \
		(fr->max.im - fr->min.im) / HEIGHT);
	while (y < fr->size)
	{
		x = 0;
		fr->c.im = fr->max.im - y * fr->factor.im;
		while (x < fr->size)
		{
			fr->c.re = fr->min.re + x * fr->factor.re;
			i = iterate (fr);
			my_mlx_pixel_put(&fr->img, x, y, get_color(i, \
			fr->max_iter, fr->color_sh));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fr->mlx, fr->mlx_win, fr->img.img, 0, 0);
}

int	iterate_mandelbrot(t_complex *c, int max_iteration)
{
	int			iteration;
	t_complex	z;
	double		p;
	double		p0;

	p = sqrt((c->re - 1 / 4) * (c->re - 1 / 4) + c->im * c->im);
	p0 = 1 / 2 - 1 / 2 * cos(atan2(c->im, c->re - 1 / 4));
	if (p <= p0)
		return (max_iteration);
	iteration = 0;
	z = init_complex(c->re, c->im);
	while (z.re * z.re + z.im * z.im <= 4
		&& iteration < max_iteration)
	{
		z = init_complex(\
			z.re * z.re - z.im * z.im + c->re, \
			2.0 * z.re * z.im + c->im);
		iteration++;
	}
	return (iteration);
}

int	paint_fractol(t_fractol *fr)
{
	char	*s;

	if (!fr->is_need_render)
		return (0);
	fr->size = WIDTH;
	if (fr->size > HEIGHT)
		fr->size = HEIGHT;
	if (FRACTOL_JULIA == fr->type)
		julia(fr);
	else if (FRACTOL_MALD == fr->type || FRACTOL_MBAR == fr->type)
		mandelbrot(fr);
	s = ft_itoa(fr->max_iter);
	mlx_string_put(fr->mlx, fr->mlx_win, 15, 15, 0x00FFFFFF, "Iteration: ");
	mlx_string_put(fr->mlx, fr->mlx_win, 120, 15, 0x00FFFFFF, s);
	fr->is_need_render = 0;
	free(s);
	return (0);
}
