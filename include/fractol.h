/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:39:54 by aguemy            #+#    #+#             */
/*   Updated: 2017/02/27 21:58:12 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define ABS(Value) ((Value < 0) ? -1 * Value : Value)
# define WIDTH 1600
# define HEIGHT 1200
# define DEPTH 50

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct	s_param
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	double			zoom;
	double			ratio;
	int				marg_i;
	int				marg_j;
}				t_param;

t_param			param_init(void *mlx, void *win, void *img, char *addr);
void			store_pixel(t_param param, int i, int j, int color);
void			mandelbrot_starter(void);
void			julia_starter(void);
int				my_key_func(int keycode, t_param *param);
char			*addr_init(void *img);
void			mandelbrot_filler(t_param param);

#endif
