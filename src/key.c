/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:23:46 by lubov             #+#    #+#             */
/*   Updated: 2022/02/01 23:14:52 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	change_max_iteration(int key, t_fractol *fr)
{
	if (MAIN_PAD_PLUS == key)
		fr->max_iter += 1;
	if (MAIN_PAD_MINUS == key)
		fr->max_iter -= 1;
}

int	key_press(int key, t_fractol *fr)
{
	if (ESC == key)
		exit(0);
	if (ARROW_UP == key || ARROW_DOWN == key
		|| ARROW_L == key || ARROW_R == key)
		move(key, fr);
	else if (BUTTON_C == key)
		fr->color_sh = ++fr->color_sh % 5;
	else if (BUTTON_V == key)
		fr->color_sh = 0;
	else if (MAIN_PAD_MINUS == key || MAIN_PAD_PLUS == key)
		change_max_iteration(key, fr);
	else if (SPACE == key)
	{
		fr->block = !fr->block;
		return (0);
	}
	fr->is_need_render = 1;
	return (0);
}
