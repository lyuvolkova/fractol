/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgrodd <qgrodd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:15:17 by qgrodd            #+#    #+#             */
/*   Updated: 2022/01/27 20:15:17 by qgrodd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void input_data_help()
{
	printf("\nIt is necessary to select the input parameter\n");
	printf("from the following:\n" );
	printf("   *Julia\n");
	printf("   *Mandelbrot\n");

}
int type_fractol(char* name_fractol)
{
	int i;

	i = FRACTOL_UNKNOWN;
	if(ft_strcmp("Julia", name_fractol))
		i = FRACTOL_JULIA;
	else if(ft_strcmp("Mandelbrot", name_fractol))
		i = FRACTOL_MALD;
	return(i);

}
void init_paint(int type)
{
	t_fractol fr;

	fr.type = type;
	fr.mlx = mlx_init();
	fr.mlx_win = mlx_new_window(fr.mlx, WIDTH, HEIGHT, "Fractol");
	fr.img.img = mlx_new_image(fr.mlx, WIDTH, HEIGHT);
	//mlx_put_image_to_window(fr.mlx, fr.mlx_win, fr.img.img, 0, 0);
	fr.img.addr = mlx_get_data_addr(fr.img.img, &fr.img.bits_per_pixel, &fr.img.line_length,
								&fr.img.endian);
	fr.min.re = -2.0;
	fr.max.re = 2.0;
	fr.min.im = -2.0;
	fr.max.im = 2.0;
	fr.color_sh = 0;
	fr.k = init_complex(-0.4, 0.6);
	fr.is_need_render = 4;
	mlx_hook(fr.mlx_win, 2, 1L << 6, key_press, &fr);
	mlx_mouse_hook(fr.mlx_win, zoom_mouse, &fr);
	mlx_loop_hook(fr.mlx, paint_fractol, &fr);
	mlx_loop(fr.mlx); 

}

int main(int argc, char** argv)
{
	int	type;

	if(argc < 2)
	{
	   input_data_help();
	   return(1);
	}
	type = type_fractol(argv[1]);
	if(FRACTOL_UNKNOWN == type)
	{
		input_data_help();
		return(1);
	}
	init_paint(type);
	return(0);
}
