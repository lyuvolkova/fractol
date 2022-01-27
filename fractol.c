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
#include "./mlx/mlx.h"

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

int main(int argc, char** argv)
{
    int     a;
    void    *mlx;
	void    *mlx_win;
    t_data img;

    
    if(argc != 2)
    {
       input_data_help();
       return(0);
    }
	
    a = type_fractol(argv[1]);
    if(FRACTOL_UNKNOWN == a)
    {
        input_data_help();
        return(0);
    }
        

    mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Fractol");
    img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    
    paint_fractol(a, &img);
    
    mlx_loop(mlx);
}