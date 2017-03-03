/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:57:20 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/03 19:29:05 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot_iter(double x, double y, t_param *param)
{
	double	tmp;

	tmp = param->z[0];
	param->z[0] = param->z[0] * param->z[0] - param->z[1] * param->z[1] + x;
	param->z[1] = 2 * tmp * param->z[1] + y;
}

void	mandelbrot_filler(t_param *param)
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
				param->z[0] = 0;
				param->z[1] = 0;
				while (depth < ITER_MAX_MANDELBROT && flag)
				{
					mandelbrot_iter(((double)j - (double)param->marg_j) /
						(double)WIDTH * 4.0 * param->zoom, ((double)i -
						(double)param->marg_i) / (double)HEIGHT * 4.0 *
						param->zoom, param);
					if (higher_than_two(param->z[0], param->z[1], 2.0))
					{
						store_pixel(param, i, j, (double)depth / (double)ITER_MAX_MANDELBROT * 0x00FFFFFF);
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

void	mandelbrot_starter(void)
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
	param.origin = 0;
	if ((param.z = (double*)malloc(sizeof(double) * 2)) && (param.c = (double*)malloc(sizeof(double) * 2)))
	{
		mandelbrot_filler(&param);
		mlx_hook(param.win, 2, 1L << 2, my_key_func, &param);
		mlx_loop(param.mlx);
	}
}
