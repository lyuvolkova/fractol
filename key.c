/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:23:46 by lubov             #+#    #+#             */
/*   Updated: 2022/02/01 00:57:44 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	color_shift(t_fractol *fr)
{
	fr->color_sh = ++fr->color_sh % 5;
}

void	change_max_iteration(int key, t_fractol *fr)
{
	if (MAIN_PAD_PLUS == key)
	{
		if (fr->max_iter< 50)
			fr->max_iter += 1;
		else if (fr->max_iter < (int)(fr->max_iter * 1.05))
			fr->max_iter= (int)(fr->max_iter * 1.05);
	}
	if (MAIN_PAD_MINUS == key)
	{
		if (fr->max_iter> 50)
			fr->max_iter = (int)(fr->max_iter * 0.95);
		else if (fr->max_iter > fr->max_iter - 1)
			fr->max_iter -= 1;
	}

	printf("%d\n", fr->max_iter);
}

int key_press(int key, t_fractol *fr)
{
	if (ESC == key)
		exit(0);
		
	if (ARROW_UP == key || ARROW_DOWN == key || ARROW_L == key || ARROW_R == key)
	{
		move(key, fr);
		fr->is_need_render = 1;
		
	}
	else if(BUTTON_C == key)
	{
		color_shift(fr);
		fr->is_need_render = 1;
		//fr->color_sh = 0;
	}
	else if(BUTTON_V == key)
	{
		fr->color_sh = 0;
		fr->is_need_render = 1;
	}
	else if(MAIN_PAD_MINUS == key || MAIN_PAD_PLUS == key)
	{
		change_max_iteration(key, fr);
		fr->is_need_render = 1;	
	}
	else if (SPACE == key)
		fr->block = !fr->block;
	return (0);
	
}