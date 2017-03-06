/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:24:57 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/06 21:21:12 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	buddhabrot_filler(t_param *param)
{
	int		depth;
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (i < RATIO)
	{
		j = 0;
		while (j < RATIO)
		{
			depth = 0;
			param->z[0] = 0.0;
			param->z[1] = 0.0;
			while (param->buff && depth < ITER_MAX && !(higher_than_two(param->z[0], param->z[1], DIVERGE)))
			{
				mandelbrot_iter(((double)j - (double)RATIO / 2.0) /
					(double)RATIO * 2.0 * SUP_BORN, ((double)i - (double)RATIO /
					2.0) / (double)RATIO * 2.0 * SUP_BORN, param);
				param->buff[depth][0] = param->z[0];
				param->buff[depth][1] = param->z[1];
				depth++;
			}
			if ((higher_than_two(param->z[0], param->z[1], DIVERGE)) && depth > ITER_MIN)
			{
				tab_update(param, depth);
				count++;
			}
			j++;
		}
		i++;
	}
	ft_putnbr(count);
	ft_putstr(" special points\n");
	ft_putstr("Tableau rempli\n");
	tab_to_pixels(param);
	ft_putstr("Image remplie\n");
	mlx_put_image_to_window(param->mlx, param->win, param->img, 50, 50);
}

void	buddha_starter(void)
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
	param.max = 0;
	param.zoom = 1.0;
	param.origin = 2;
	param.marg_i = HEIGHT / 2;
	param.marg_j = WIDTH / 2;
	param.buff = memory_buffer();
	if ((param.z = (double*)malloc(sizeof(double) * 2)) && (param.c = (double*)malloc(sizeof(double) * 2)))
	{
		buddhabrot_filler(&param);
		mlx_hook(param.win, 2, 1L << 2, my_key_func, &param);
		mlx_loop(param.mlx);
	}
}
