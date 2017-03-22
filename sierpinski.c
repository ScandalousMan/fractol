/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 12:29:25 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/15 20:22:41 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		zoom_to_ratio(double zoom)
{
	int		i;

	i = 1;
	if (zoom != 0.0)
	{
//		zoom = 1.0 / zoom;
		while ((int)trunc(zoom) / 3 != 0)
		{
			i = i * 3;
			zoom = zoom / 3.0;
		}
	}
	return (i);
}

int		sierpinski_carpet(int si1, int si2)
{
	while (si1 > 0 && si2 > 0)
	{
		if (si1 % 3 == 1 && si2 % 3 == 1)
			return (0);
		si1 /= 3;
		si2 /= 3;
	}
	return (1);
}



void	sierpinski_filler(t_param *param)
{
	if ((double)HEIGHT * param->zoom / (double)param->max / (double)SIDE > 1.0)
		param->max *= 3;
	param->si[0] = 0;
	while (param->si[0] < param->max * SIDE) // && (param->zoom < 1.0 || param->si[0] < (int)trunc(param->max * SIDE / (double)param->zoom)))
	{
		param->si[1] = 0;
		while (param->si[1] < param->max * SIDE) // && (param->zoom < 1.0 || param->si[0] < (int)trunc(param->max * SIDE / (double)param->zoom)))
		{
			if (sierpinski_carpet(param->si[0], param->si[1]))
				store_pixel(param, (int)((double)(param->si[0] - param->max * SIDE / 2) * (double)HEIGHT * param->zoom / param->max / (double)SIDE) + param->marg_i,
					(int)((double)(param->si[1] - param->max * SIDE / 2) * (double)WIDTH / param->max / (double)SIDE * param->zoom) + param->marg_j, 0x00FFFFFF);
			(param->si[1])++;
		}
		(param->si[0])++;
	}
	mlx_put_image_to_window(param->mlx, param->win, param->img, 50, 50);
}

void	sierpinski_starter(void)
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	t_param	param;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH + 100, HEIGHT + 100, "Fract'ol aguemy");
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	addr = addr_init(img);
	param = param_init(mlx, win, img, addr);
	param.tab = tab_init();
	param.max = 1;
	param.zoom = 1.0;
	param.origin = 5;
	param.marg_i = HEIGHT / 2;
	param.marg_j = WIDTH / 2;
	param.buff = memory_buffer();
	if ((param.si = (int*)malloc(sizeof(int) * 2)) && (param.c = (double*)malloc(sizeof(double) * 2)))
	{
		sierpinski_filler(&param);
		mlx_hook(param.win, 2, 1L << 2, my_key_func, &param);
		mlx_mouse_hook(param.win, my_mouse_hook, &param);
		mlx_loop(param.mlx);
	}
}
