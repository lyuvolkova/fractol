/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgrodd <qgrodd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:52:38 by qgrodd            #+#    #+#             */
/*   Updated: 2022/01/27 21:03:33 by qgrodd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int julia_motion(int x, int y, t_complex *k)
{
    k = init_complex(
        4 * ((double)x / WIDTH - 0.5),
        4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
    //
    return (0);
}