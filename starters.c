/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:44:10 by aguemy            #+#    #+#             */
/*   Updated: 2017/05/08 15:18:30 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	param_zc_init(int argc, char **argv, t_param *param)
{
	if (argc == 4)
	{
		param->c[0] = ft_atod(argv[2]);
		param->c[1] = ft_atod(argv[3]);
	}
	else if (param->origin == 1)
	{
		param->c[0] = 0.285;
		param->c[1] = 0.01;
	}
	else if (param->origin == 3)
	{
		param->c[0] = -0.621;
		param->c[1] = 0.0;
	}
	else if (param->origin == 5)
	{
		param->c[0] = 0.4;
		param->c[1] = 0.0;
	}
	else if (param->origin == 6)
	{
		param->c[0] = 0.21;
		param->c[1] = 0.0;
	}
}

t_param	*generic_starter(t_mlx *multi)
{
	t_param	*param;

	if (!(param = (t_param*)malloc(sizeof(t_param))) ||
			!(param->z = (double*)malloc(sizeof(double) * 2)) ||
			!(param->c = (double*)malloc(sizeof(double) * 2)))
		return (NULL);
	if (multi && multi->mlx)
	{
		multi->param[multi->ref] = param;
		param->mlx = multi->mlx;
	}
	else if (!(param->mlx = mlx_init()))
		return (NULL);
	if (!(param->win = mlx_new_window(param->mlx, WIDTH + 100, HEIGHT + 100,
			"Fract'ol aguemy")) || !(param->img = mlx_new_image(param->mlx,
			WIDTH, HEIGHT)) || !(param->addr = addr_init(param->img)))
		return (NULL);
	param->marg_i = HEIGHT / 2;
	param->marg_j = WIDTH / 2;
	param->col = 0x00FF5379;
	param->mouse_param_modifier = 0;
	param->ratio = 4.0 / (double)(ft_min(HEIGHT, WIDTH));
	return (param);
}

void	generic_launcher(t_param *param)
{
	if (param)
	{
		generic_filler(param);
		mlx_hook(param->win, 2, 1L << 2, my_key_func, param);
		mlx_hook(param->win, 6, 1L << 6, my_pointer_motion, param);
		mlx_mouse_hook(param->win, my_mouse_hook, param);
		mlx_loop(param->mlx);
	}
	else
		ft_putstr("One malloc failed\n");
}

void	mandelbrot_starter(t_mlx *multi)
{
	t_param	*param;

	param = generic_starter(multi);
	if (param)
	{
		param->origin = 0;
		param->zoom = 1.0;
		param->algo = mandelbrot_algo;
		param->iter = mandelbrot_iter;
	}
	generic_launcher(param);
}

void	julia_starter(int argc, char **argv, t_mlx *multi)
{
	t_param	*param;

	param = generic_starter(multi);
	if (param)
	{
		param->origin = 1;
		param->zoom = 1.0;
		param->algo = julia_algo;
		param->iter = mandelbrot_iter;
		param_zc_init(argc, argv, param);
	}
	generic_launcher(param);
}
