/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:39:54 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/03 19:16:07 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define ABS(Value) ((Value < 0) ? -1 * Value : Value)
# define WIDTH 1200
# define HEIGHT 1200
# define ITER_MAX 1500
# define ITER_MIN 50
# define ITER_MAX_MANDELBROT 50
# define RATIO 800
# define DIVERGE 2.0
# define SUP_BORN 1.5
# define RED 155
# define GREEN 200
# define BLUE 255

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct	s_param
{
	double			*z;
	double			*c;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	double			zoom;
	double			ratio;
	int				marg_i;
	int				marg_j;
	int				**tab;
	int				max;
	double			**buff;
	int				origin;
}				t_param;

t_param			param_init(void *mlx, void *win, void *img, char *addr);
int				rgb_color(unsigned char r, unsigned char g, unsigned char b);
void			store_pixel(t_param *param, int i, int j, int color);
void			mandelbrot_starter(void);
void			julia_starter(void);
void			buddha_starter(void);
int				my_key_func(int keycode, t_param *param);
char			*addr_init(void *img);
void			mandelbrot_filler(t_param *param);
void			julia_filler(t_param *param);
void			buddhabrot_filler(t_param *param);
int				higher_than_two(double x, double y, double two);//x2 + y2 < 4 ?
void			mandelbrot_iter(double x, double y, t_param *param);//Zn+1 = Zn2 + c

#endif
