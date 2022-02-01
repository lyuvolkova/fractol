/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgrodd <qgrodd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:16:46 by qgrodd            #+#    #+#             */
/*   Updated: 2022/01/27 20:16:46 by qgrodd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] != '\0' || s2[i] != '\0' || s1[i] != s2[i])
		return (0);
	return (1);
}

t_complex	init_complex(double re, double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	iterate(t_fractol *fr)
{
	int			i;
	t_complex	z;
	double		p;
	double		p0;

	if (FRACTOL_MBAR == fr->type)
	{
		i = 0;
		p = sqrt((fr->c.re - 1 / 4) * (fr->c.re - 1 / 4) + fr->c.im * fr->c.im);
		p0 = 1 / 2 - 1 / 2 * cos(atan2(fr->c.im, fr->c.re - 1 / 4));
		if (p <= p0)
			return (fr->max_iter);
		z = init_complex(fr->c.re, fr->c.im);
		while (z.re * z.re + z.im * z.im <= 4 \
			&& i < fr->max_iter)
		{
			z = init_complex(z.re * z.re - z.im * z.im + fr->c.re, \
			-2.0 * z.re * z.im + fr->c.im);
			i++;
		}
	}
	else
		i = iterate_mandelbrot(&fr->c, fr->max_iter);
	return (i);
}

int	get_color(int i, int iteration_count, int sh)
{
	double	t;
	int		c[3];

	t = (double)i / (double)iteration_count;
	if (sh > 1)
	{
		c[1] = (int)((sh + 1) % 3 * (90 * (1 - t) * t * t * t * 255));
		c[2] = (int)((2 + sh) % 3 * (150 * (1 - t) * (1 - t) * t * t * 255));
		c[0] = (int)((3 + sh) % 3 * (80 * (1 - t) * (1 - t) * (1 - t) * \
		t * 255));
	}
	else if (sh == 1)
	{
		c[2] = (int)(9 * (1 - t) * t * t * t * 255);
		c[0] = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		c[1] = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	else
	{
		c[0] = (int)(9 * (1 - t) * t * t * t * 255);
		c[1] = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		c[2] = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	return (c[0] << 16 | c[1] << 8 | c[2]);
}
