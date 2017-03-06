/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 19:41:01 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/06 21:25:10 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia_exp_iter(double x, double y, t_param *param)
{
	double	tmp;

	tmp = param->z[0];
	param->z[0] = (param->z[0] * param->z[0] - param->z[1] * param->z[1]) *
		param->z[0] - param->z[1] * 2.0 * param->z[0] * param->z[1];
	param->z[1] = 2.0 * tmp * param->z[1] * tmp + param->z[1] *
		(tmp * tmp - param->z[1] * param->z[1]);
	tmp = exp(param->z[0]);
	param->z[0] = tmp * cos(param->z[1]) + x;
	param->z[1] = tmp * sin(param->z[1]) + y;
}

void	julia_exp_filler(t_param *param)
{
	int		depth;
	int		i;
	int		j;
	double		*z;
	int		flag;

	i = 0;
	if ((z = (double*)malloc(sizeof(double) * 2)))
	{
		while (i < HEIGHT)
		{
			j = 0;
			while (j < WIDTH)
			{
				flag = 1;
				depth = 0;
				param->z[0] = ((double)j - (double)param->marg_j) / (double)WIDTH * SUP_BORN * 4.0 * param->zoom;
				param->z[1] = ((double)param->marg_i - (double)i) / (double)HEIGHT * SUP_BORN * 4.0 * param->zoom;
				while (depth < ITER_MAX_JULIA_EXP && flag)
				{
					julia_exp_iter(param->c[0], param->c[1], param);
					if (higher_than_two(param->z[0], param->z[1], JULIA_MODULE))
					{
						store_pixel(param, i, j, (double)depth / (double)ITER_MAX_JULIA_EXP * 0x00FFFFFF);
						flag = 0;
					}
					depth++;
				}
				j++;
			}
			i++;
		}
	}
	mlx_put_image_to_window(param->mlx, param->win, param->img, 50, 50);
}

void	julia_exp_starter(int argc, char **argv)
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
	param.origin = 3;
	if ((param.z = (double*)malloc(sizeof(double) * 2)) && (param.c = (double*)malloc(sizeof(double) * 2)))
	{
		if (argc == 4)
		{
			param.c[0] = ft_atod(argv[2]);
			param.c[1] = ft_atod(argv[3]);
		}
		else
		{
			param.c[0] = -0.621;
			param.c[1] = 0.0;
		}
		julia_exp_filler(&param);
		mlx_hook(param.win, 2, 1L << 2, my_key_func, &param);
		mlx_loop(param.mlx);
	}
}
