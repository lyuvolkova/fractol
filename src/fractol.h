/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgrodd <qgrodd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:16:34 by qgrodd            #+#    #+#             */
/*   Updated: 2022/01/27 20:16:34 by qgrodd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "stdio.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# define FRACTOL_UNKNOWN	0
# define FRACTOL_JULIA		1
# define FRACTOL_MALD		2
# define FRACTOL_MBAR		3
# define HEIGHT				800
# define WIDTH				800
# define MAX_ITERATION		50
# define ESC				53
# define PAD_R				15
# define ARROW_UP			126
# define ARROW_DOWN			125
# define ARROW_R			124
# define ARROW_L			123
# define SCROLL_UP			4
# define SCROLL_DOWN		5
# define BUTTON_C 			8
# define BUTTON_V			9
# define MAIN_PAD_PLUS		24
# define MAIN_PAD_MINUS		27
# define SPACE 				49
# define NUM_PAD_PLUS		69
# define NUM_PAD_MINUS		78

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_complex
{
	double	re;
	double	im;
}				t_complex;

typedef struct s_fractol
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	int			size;
	int			type;
	t_complex	c;
	t_complex	min;
	t_complex	max;
	t_complex	k;
	t_complex	factor;
	int			is_need_render;
	int			color_sh;
	int			max_iter;
	int			block;
}				t_fractol;

int			key_press(int key, t_fractol *fr);
int			iterate(t_fractol *fr);
int			get_color(int i, int iteration_count, int sh);
int			julia_motion(int x, int y, t_fractol *fr);
int			ft_strcmp(char *s1, char *s2);
void		move(int key, t_fractol *fr);
int			paint_fractol(t_fractol *fr);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			iterate_mandelbrot(t_complex *c, int max_iteration);
int			zoom_mouse(int type, int x, int y, t_fractol *fr);
t_complex	init_complex(double re, double im);
char		*ft_itoa(int n);

#endif