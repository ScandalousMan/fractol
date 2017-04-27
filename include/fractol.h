/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:39:54 by aguemy            #+#    #+#             */
/*   Updated: 2017/04/27 17:57:01 by aguemy           ###   ########.fr       */
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

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
#include <pthread.h>
# include "../libft/libft.h"

typedef struct	s_param
{
	pthread_t		*threads;
	int				i;
	int				j;
	int				k;
	int				tmp;
	int				count;
	int				max;
	int				col;
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
	double			**buff;
	int				origin;
	int				flag;
	int				depth;
	int				mouse_param_modifier;
	void			(*algo)(struct s_param *);
	void			(*iter)(double, double, struct s_param *);
}				t_param;

/*
**------------------------Structures pour fractales 3D--------------------------
*/

/*
**----------------Utilitaires generiques pour fractales-------------------------
*/
double			ft_atod(const char *str);
int				rgb_color(unsigned char r, unsigned char g, unsigned char b);
void			store_pixel(t_param *param, int color);
int				higher_than_two(double x, double y, double two);
void			color_wheel(t_param *param);
/*
**----------------------Iterations of different suites--------------------------
*/
void			mandelbrot_iter(double x, double y, t_param *param);
void			julia_exp_iter(double x, double y, t_param *param);
void			julia_iter(double x, double y, t_param *param);
void			burning_iter(double x, double y, t_param *param);
void			julia_cube_iter(double x, double y, t_param *param);
void			julia_flower_iter(double x, double y, t_param *param);
/*
**---------------------Starters of different fractals---------------------------
*/
void			param_zc_init(int argc, char **argv, t_param *param);
t_param			*generic_starter();
void			generic_launcher(t_param *param);
void			mandelbrot_starter(void);
void			julia_starter(int argc, char **str);
void			julia_exp_starter(int argc, char **str);
void			julia_cube_starter(int argc, char **str);
void			julia_flower_starter(int argc, char **str);
void			buddha_starter(void);
void			burning_ship_starter(void);
/*
**----------------------Filler des differentes fractales-----------------------
*/
//void			mandelbrot_filler(t_param *param);
void			generic_filler(t_param *param);
//void			julia_exp_filler(t_param *param);
//void			buddhabrot_filler(t_param *param);
/*
**--------------------------------Algorithms------------------------------------
*/
void			mandelbrot_algo(t_param *param);
void			julia_algo(t_param *param);
void			buddhabrot_algo(t_param *param);
/*
**-----------------------------------------------------------------------------
*/
int				my_key_func(int keycode, t_param *param);
int				my_mouse_hook(int button, int x, int y, t_param *param);
int				my_pointer_motion(int x, int y, t_param *param);
void			back_to_function(t_param *param);
char			*addr_init(void *img);
/*
**-----------------Components for Buddhabrot------------------------------------
*/
int				buddha_color(t_param *param);
void			tab_to_pixels(t_param *param);
void			tab_update(t_param *param);
double			**memory_buffer(void);
int				**tab_init(void);

#endif
