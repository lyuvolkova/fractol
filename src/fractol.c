/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:15:17 by qgrodd            #+#    #+#             */
/*   Updated: 2022/02/01 20:53:00 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	input_data_help(void)
{
	printf("\nIt is necessary to select the input parameter\n");
	printf("from the following:\n" );
	printf("   *Julia\n");
	printf("   *Mandelbrot\n");
	printf("   *Mandelbar\n");
}

int	type_fractol(char *name_fractol)
{
	int	i;

	i = FRACTOL_UNKNOWN;
	if (ft_strcmp("Julia", name_fractol))
		i = FRACTOL_JULIA;
	else if (ft_strcmp("Mandelbrot", name_fractol))
		i = FRACTOL_MALD;
	else if (ft_strcmp("Mandelbar", name_fractol))
		i = FRACTOL_MBAR;
	return (i);
}

void	init_paint(int type)
{
	t_fractol	fr;

	fr.type = type;
	fr.mlx = mlx_init();
	fr.mlx_win = mlx_new_window(fr.mlx, WIDTH, HEIGHT, "Fractol");
	fr.img.img = mlx_new_image(fr.mlx, WIDTH, HEIGHT);
	fr.img.addr = mlx_get_data_addr(fr.img.img, &fr.img.bits_per_pixel, \
	&fr.img.line_length, &fr.img.endian);
	fr.min = init_complex(-2.0, -2.0);
	fr.max = init_complex(2.0, 2.0);
	fr.color_sh = 0;
	fr.max_iter = MAX_ITERATION;
	fr.block = 0;
	fr.k = init_complex(0.6, -0.4);
	fr.is_need_render = 4;
	mlx_key_hook(fr.mlx_win, key_press, &fr);
	mlx_mouse_hook(fr.mlx_win, zoom_mouse, &fr);
	mlx_loop_hook(fr.mlx, paint_fractol, &fr);
	if (FRACTOL_JULIA == fr.type)
		mlx_hook(fr.mlx_win, 6, 2L << 6, julia_motion, &fr);
	mlx_loop(fr.mlx);
}

int	main(int argc, char **argv)
{
	int	type;

	if (argc < 2)
	{
		input_data_help();
		return (1);
	}
	type = type_fractol(argv[1]);
	if (FRACTOL_UNKNOWN == type)
	{
		input_data_help();
		return (1);
	}
	init_paint(type);
	return (0);
}
