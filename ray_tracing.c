/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:25:49 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/22 22:27:56 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

t_param	param_init(void *mlx, void *win, void *img, char *addr)
{
	t_param	param;

	param.mlx = mlx;
	param.win = win;
	param.img = img;
	param.addr = addr;
	param.marg_i = HEIGHT / 2;
	param.marg_j = WIDTH / 2;
	param.zoom = 1;
	param.ratio = 4 / (double)(ft_min(HEIGHT, WIDTH));
	return (param);
}

int		sierpinski_algo(int si1, int si2, int si3)
{
	if (si1 < 0 || si2 < 0 || si3 < 0 || si1 > 728 || si2 > 728 || si3 > 728)
		return (0);
	while ((si1 > 0 && (si2 > 0 || si3 > 0)) || (si2 > 0 && si3 > 0))
	{
		if ((si1 % 3 == 1 && (si2 % 3 == 1 || si3 % 3 == 1)) ||
				(si2 % 3 == 1 && si3 % 3 == 1))
			return (0);
		si1 /= 3;
		si2 /= 3;
		si3 /= 3;
	}
	return (1);
}

int		sierpinski_carpet(double x, double y, double z, t_param *param)
{
	int	si1;
	int	si2;
	int	si3;
	int	i;

	i = 1;
	if (x > param->x_init[0] + param->x[3] || x < param->x_init[0] ||
			y > param->x_init[1] + param->x[3] || y < param->x_init[1] ||
			z > param->x_init[2] + param->x[3] || z < param->x_init[2])
		return (0);
	si1 = (int)trunc((x - param->x_init[0]) / param->x[3] * 728);
	si2 = (int)trunc((y - param->x_init[1]) / param->x[3] * 728);
	si3 = (int)trunc((z - param->x_init[2]) / param->x[3] * 728);
	if (sierpinski_algo(si1, si2, si3))
	{
		if (sierpinski_algo(si1, si2, si3 - 1) != 0)
			return (1);
		else if (sierpinski_algo(si1 - 1, si2, si3) != 0)
			return (2);
		else if (sierpinski_algo(si1 , si2 - 1, si3) != 0)
			return (3);
	}
	return (0);
}

char	*addr_init(void *img)
{
	char	*addr;
	int		detail[3];

	detail[0] = 4;
	detail[1] = WIDTH * 4;
	detail[2] = 0;
	addr = mlx_get_data_addr(img, &(detail[0]), &(detail[1]), &(detail[2]));
	ft_bzero(addr, HEIGHT * WIDTH * 4);
	return (addr);
}

void	store_pixel(t_param *param, int i, int j, int color)
{
	if (i >= 0 && i < HEIGHT && j >= 0 && j < WIDTH)
	{
		param->addr[(i * WIDTH + j) * 4 + 2] = (color) & 0xFF;
		param->addr[(i * WIDTH + j) * 4 + 1] = (color >> 8) & 0xFF;
		param->addr[(i * WIDTH + j) * 4 + 0] = (color >> 16) & 0xFF;
	}
}

void	rt_filler(t_param *param)
{
	int		i;
	int		j;
	double	y[3]; // y est le vecteur allant de l'oeil au centre de la sphere 2
	double	v[3]; // v est le vecteur lié au point (i, j)
	double	src[3];
	double	R;
	int		a;
	int		tmp;
	double	b;
	double	beta;

	i = 0;
//	b = -1.0;
	param->x_init[0] = 10.0;
	param->x_init[1] = 4.0;
	param->x_init[2] = 60.0;
	param->x[0] = param->x_init[0];
	param->x[1] = param->x_init[1];
	param->x[3] = 20.0;
	src[0] = 0.0;
	src[1] = 28.0;
	src[2] = 0.0;
	v[2] = 40.0; //focale : distance entre oeil et ecran
	ft_putstr("On commence\n");
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			param->x[2] = param->x_init[2];
			a = 0;
			v[0] = ((double)i - (double)HEIGHT / 2.0) * v[2] / (double)HEIGHT;
			v[1] = ((double)j - (double)WIDTH / 2.0) * v[2] / (double)WIDTH;
			while (param->x[2] < param->x_init[2] + param->x[3] && a == 0)
			{
				if ((tmp = sierpinski_carpet(param->x[2] * v[0] / v[2], param->x[2] * v[1] / v[2], param->x[2], param)))
				{
					if (param->x[2] == param->x_init[2] || tmp == 1)
						store_pixel(param, i, j, 0x000000FF);
					else if (param->x[2] * v[0] / v[2] == param->x_init[0] || tmp == 2)
						store_pixel(param, i, j, 0x0000FF00);
					else if (param->x[2] * v[1] / v[2] == param->x_init[1] || tmp == 3)
						store_pixel(param, i, j, 0x00FF0000);
					/*b = b / sqrt((src[0] - param->x[2] * v[0] / v[2]) * (src[0] - param->x[2] * v[0] / v[2]) +
							(src[1] - param->x[2] * v[1] / v[2]) * (src[1] - param->x[2] * v[1] / v[2]) +
							(src[2] - param->x[2]) * (src[2] - param->x[2]));
					if (b < 0.0)
						b = 0.0;*/
//					store_pixel(param, i, j, 0x000000FF * (0.85 * b + 0.15));
//					store_pixel(param, i, j, trunc((param->x[2] - param->x_init[2]) / param->x[3] * 255) * 255 + 255);
					a = 1;
				}
				param->x[2] += param->x[3] / 729;
			}
			j++;
		}
		i++;
	}
	ft_putstr("On finit\n");
	mlx_put_image_to_window(param->mlx, param->win, param->img, 50, 50);
	ft_putstr("On a trace\n");
}

void	rt_starter(void)
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
	if ((param.z = (double*)malloc(sizeof(double) * 2)) &&
			(param.c = (double*)malloc(sizeof(double) * 2)) &&
			(param.x = (double*)malloc(sizeof(double) * 4)) &&
			(param.x_init = (double*)malloc(sizeof(double) * 3)))
	{
		rt_filler(&param);
		mlx_loop(param.mlx);
	}
}

int		main(void)
{
	rt_starter();
	return (0);
}
