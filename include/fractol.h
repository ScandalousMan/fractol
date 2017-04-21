/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:39:54 by aguemy            #+#    #+#             */
/*   Updated: 2017/04/21 15:22:09 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define ABS(Value) ((Value < 0) ? -1 * Value : Value)
# define WIDTH 1200
# define HEIGHT 1200
# define DEPTH 1200
# define ITER_MAX 1500
# define ITER_MIN 50
# define ITER_MAX_MANDELBROT 50
# define ITER_MAX_JULIA 50
# define ITER_MAX_JULIA_EXP 500
# define JULIA_MODULE 1000
# define SIDE 729
# define RATIO 800
# define DIVERGE 2.0
# define SUP_BORN 1.5
# define ZOOM_PARAM 1.1
# define RED 155
# define GREEN 200
# define BLUE 255
# define SI_LVL 729

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct	s_param
{
	int				*sponge;
	double			*x;
	double			*x_init;
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
	int				*si;
	int				max;
	double			**buff;
	int				origin;
	double			*ref;
	double			*n;
	double			*src;
}				t_param;

/*
**------------------------Structures pour fractales 3D--------------------------
*/

/*
**----------------Utilitaires generiques pour fractales-------------------------
*/
double			ft_atod(const char *str);
t_param			param_init(void *mlx, void *win, void *img, char *addr);
int				rgb_color(unsigned char r, unsigned char g, unsigned char b);
void			store_pixel(t_param *param, int i, int j, int color);
int				higher_than_two(double x, double y, double two);
void			mandelbrot_iter(double x, double y, t_param *param);
/*
**--------------------Starter des differentes fractales-------------------------
*/
void			mandelbrot_starter(void);
void			julia_starter(int argc, char **str);
void			julia_exp_starter(int argc, char **str);
void			buddha_starter(void);
/*
**----------------------Filler des differentes fractales-----------------------
*/
void			mandelbrot_filler(t_param *param);
void			julia_filler(t_param *param);
void			julia_exp_filler(t_param *param);
void			buddhabrot_filler(t_param *param);

int				my_key_func(int keycode, t_param *param);
int				my_mouse_hook(int button, int x, int y, t_param *param);
void			back_to_function(t_param *param);
char			*addr_init(void *img);
/*
**-----------------Components for Buddhabrot------------------------------------
*/
int				buddha_color(int i, int j, t_param *param);
void			tab_to_pixels(t_param *param);
void			tab_update(t_param *param, int depth);
double			**memory_buffer(void);
int				**tab_init(void);

#endif
