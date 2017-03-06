/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:57:27 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/06 21:33:29 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia_filler_core(int i, int j, t_param *param)
{
	int		flag;
	int		depth;

	flag = 1;
	depth = 0;
	param->z[0] = ((double)j - (double)param->marg_j) / (double)WIDTH *
		SUP_BORN * 2.0 * param->zoom;
	param->z[1] = ((double)param->marg_i - (double)i) / (double)HEIGHT *
		SUP_BORN * 2.0 * param->zoom;
	while (depth < ITER_MAX_JULIA && flag)
	{
		mandelbrot_iter(param->c[0], param->c[1], param);
		if (higher_than_two(param->z[0], param->z[1], 2.0))
		{
			store_pixel(param, i, j, (double)depth / (double)ITER_MAX_JULIA *
				0x00FFFFFF);
			flag = 0;
		}
		depth++;
	}
}

void	julia_filler(t_param *param)
{
	int		i;
	int		j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			julia_filler_core(i, j, param);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(param->mlx, param->win, param->img, 50, 50);
}

void	param_zc_init(int argc, char **argv, t_param *param)
{
	if ((param->z = (double*)malloc(sizeof(double) * 2)) &&
			(param->c = (double*)malloc(sizeof(double) * 2)))
	{
		if (argc == 4)
		{
			param->c[0] = ft_atod(argv[2]);
			param->c[1] = ft_atod(argv[3]);
		}
		else
		{
			param->c[0] = 0.285;
			param->c[1] = 0.01;
		}
		julia_filler(param);
		mlx_hook(param->win, 2, 1L << 2, my_key_func, param);
		mlx_loop(param->mlx);
	}
}

void	julia_starter(int argc, char **argv)
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
	param.marg_i = HEIGHT / 2;
	param.marg_j = WIDTH / 2;
	param.origin = 1;
	param_zc_init(argc, argv, &param);
}
