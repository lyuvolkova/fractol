/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:52:38 by qgrodd            #+#    #+#             */
/*   Updated: 2022/02/01 00:31:15 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int julia_motion(int x, int y, t_fractol *fr)
{
	if(fr->block != 0)
	{
		fr->k = init_complex(
		4 * ((double)x / WIDTH - 0.5),
		4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
		fr->is_need_render = 1;
	}	
	return (0);
}

void move(int key, t_fractol *fr)
{
	t_complex d;

	d = init_complex(fabs(fr->max.re - fr->min.re),
					fabs(fr->max.im - fr->min.im));
	if (ARROW_UP == key)
	{
		fr->min.im -= d.im * 0.05;
		fr->max.im -= d.im * 0.05;	
	}
	else if(ARROW_DOWN == key)
	{
		fr->min.im += d.im * 0.05;
		fr->max.im += d.im * 0.05;
	}
	else if (ARROW_L == key)
	{
		fr->min.re += d.re * 0.05;
		fr->max.re += d.re * 0.05;	
	}
	else if (ARROW_R == key)
	{
		fr->min.re -= d.re * 0.05;
		fr->max.re -= d.re * 0.05;	
	}
}

double	interpolate(double start, double end, double param)
{
	return (start + ((end - start) * param));
}

int	zoom_mouse(int type, int x, int y, t_fractol *fr)
{
	t_complex	mouse;
	double		param;

	if (SCROLL_UP == type || SCROLL_DOWN == type)
	{
		mouse = init_complex(x * 4 / WIDTH, y * 4 / HEIGHT);
		if (SCROLL_DOWN == type)
			param = 0.80;
		else
			param = 1.20;
		fr->min.re = interpolate(mouse.re, fr->min.re, param);
		fr->min.im = interpolate(mouse.im, fr->min.im, param);
		fr->max.re = interpolate(mouse.re, fr->max.re, param);
		fr->max.im = interpolate(mouse.im, fr->max.im, param);
		fr->is_need_render = 1;
	}
	return(0);
}
