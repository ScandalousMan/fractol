/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:57:20 by aguemy            #+#    #+#             */
/*   Updated: 2017/02/27 21:35:04 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		higher_than_two(double x, double y, t_param param)
{
	if (param.ratio * param.ratio * (x * x + y * y) < 4)
		return (0);
	return (1);
}

void	mandelbrot_iter(double **z, int i, int j, t_param param)
{
	double	tmp;

	tmp = (*z)[0];
	(*z)[0] = (*z)[0] * (*z)[0] - (*z)[1] * (*z)[1] +
		((double)i - (double)WIDTH / 2) * param.ratio;
	(*z)[1] = 2 * tmp * (*z)[1] + ((double)j - (double)HEIGHT / 2) * param.ratio;
}

void	mandelbrot_filler(t_param param)
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
				z[0] = 0;
				z[1] = 0;
				while (depth < DEPTH && flag)
				{
					mandelbrot_iter(&z, j, i, param);
					if (higher_than_two(z[0], z[1], param))
					{
						store_pixel(param, i, j, (double)depth / DEPTH * 0x00FFFFFF);
						flag = 0;
					}
/*					else
					{
						ft_putstr("(i,j,depth) = ");
						ft_putnbr(i);
						ft_putstr(",");
						ft_putnbr(j);
						ft_putstr(",");
						ft_putnbr(depth);
						ft_putstr(")\n");
					}*/
					depth++;
				}
				j++;
			}
			i++;
		}
	}
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
	mandelbrot_filler(param);
	mlx_put_image_to_window(mlx, win, img, 50, 50);
	mlx_hook(param.win, 2, 1L << 2, my_key_func, &param);
	mlx_loop(param.mlx);
}
