/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starters2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:44:10 by aguemy            #+#    #+#             */
/*   Updated: 2017/04/30 15:03:19 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	buddha_starter(void)
{
	t_param *param;

	param = generic_starter();
	if (param)
	{
		param->origin = 2;
		param->zoom = 1.0;
		param->algo = buddhabrot_algo;
		param->iter = mandelbrot_iter;
		param->max = 0;
		param->tmp = -1;
		param->tab = tab_init();
		param->buff = memory_buffer();
	}
	generic_filler(param);
	mlx_hook(param->win, 2, 1L << 2, my_key_func, param);
	mlx_mouse_hook(param->win, my_mouse_hook, param);
	mlx_loop(param->mlx);
}

void	burning_ship_starter(void)
{
	t_param *param;

	param = generic_starter();
	if (param)
	{
		param->origin = 4;
		param->zoom = 1.0;
		param->algo = mandelbrot_algo;
		param->iter = burning_iter;
	}
	generic_launcher(param);
}

void	julia_exp_starter(int argc, char **argv)
{
	t_param	*param;

	param = generic_starter();
	if (param)
	{
		param->origin = 3;
		param->zoom = 2.0;
		param->algo = julia_algo;
		param->iter = julia_exp_iter;
		param_zc_init(argc, argv, param);
	}
	generic_launcher(param);
}

void	julia_cube_starter(int argc, char **argv)
{
	t_param	*param;

	param = generic_starter();
	if (param)
	{
		param->origin = 5;
		param->zoom = 2.0;
		param->algo = julia_algo;
		param->iter = julia_cube_iter;
		param_zc_init(argc, argv, param);
	}
	generic_launcher(param);
}

void	julia_flower_starter(int argc, char **argv)
{
	t_param	*param;

	param = generic_starter();
	if (param)
	{
		param->origin = 6;
		param->zoom = 0.5;
		param->algo = julia_algo;
		param->iter = julia_flower_iter;
		param_zc_init(argc, argv, param);
	}
	generic_launcher(param);
}
