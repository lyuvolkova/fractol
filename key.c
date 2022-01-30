/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:23:46 by lubov             #+#    #+#             */
/*   Updated: 2022/01/30 17:50:49 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	color_shift(t_fractol *fr)
{
	fr->color_sh += 1;
}

int key_press(int key, t_fractol *fr)
{
	if (ESC == key)
		exit(0);
		
	if (ARROW_UP == key || ARROW_DOWN == key || ARROW_L == key || ARROW_R == key)
	{
		//julia_motion(400,400,fr);;
		// printf("%s", "ok; ");
		move(key, fr);
		
		//paint_fractol(fr);
		//mlx_sync(2, fr->img);
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
	//else if()
	
	return (0);
	
}