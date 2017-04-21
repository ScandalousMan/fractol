/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:25:49 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/29 11:50:53 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

void	view_check(double x, double y, double z, t_param *param)
{
	if (x > 0.0)
		param->ref[0] = -param->x[3] / (double)SI_LVL;
	else
		param->ref[0] = param->x[3] / (double)SI_LVL;
	if (y > 0.0)
		param->ref[1] = -param->x[3] / (double)SI_LVL;
	else
		param->ref[1] = param->x[3] / (double)SI_LVL;
	if (z > 40.0)
		param->ref[2] = -param->x[3] / (double)SI_LVL;
	else
		param->ref[2] = param->x[3] / (double)SI_LVL;
}

void	normed_color(double x, double y , double z, t_param *param)
{
	param->n[0] = (x - param->src[0]) / sqrt((param->src[0] - x) *
		(param->src[0] - x) + (param->src[1] - y) * (param->src[1] - y) +
		(param->src[2] - z) * (param->src[2] - z));
	param->n[1] = (y - param->src[1]) / sqrt((param->src[0] - x) *
		(param->src[0] - x) + (param->src[1] - y) * (param->src[1] - y) +
		(param->src[2] - z) * (param->src[2] - z));
	param->n[2] = (z - param->src[2]) / sqrt((param->src[0] - x) *
		(param->src[0] - x) + (param->src[1] - y) * (param->src[1] - y) +
		(param->src[2] - z) * (param->src[2] - z));
	if (param->n[0] < 0)
		param->n[0] = 0;
	if (param->n[1] < 0)
		param->n[1] = 0;
	if (param->n[2] < 0)
		param->n[2] = 0;
}

void	rt_filler(t_param *param)
{
	int		i;
	int		j;
	double	v[3]; // v est le vecteur lié au point (i, j)
	int		a;

	i = 0;
	param->x_init[0] = 9.0;
	param->x_init[1] = 9.0;
	param->x_init[2] = 50.0;
	param->x[0] = param->x_init[0];
	param->x[1] = param->x_init[1];
	param->x[3] = 10.0;
	param->src[0] = 0.0;
	param->src[1] = 28.0;
	param->src[2] = 0.0;
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
				if (sierpinski_carpet(param->x[2] * v[0] / v[2], param->x[2] * v[1] / v[2], param->x[2], param))
				{
					view_check(param->x[2] * v[0] / v[2], param->x[2] * v[1] / v[2], param->x[2], param);
					if (!sierpinski_carpet(param->x[2] * v[0] / v[2],
						param->x[2] * v[1] / v[2], param->x[2] + param->ref[2], param))
						store_pixel(param, i, j, 0x000000FF * (0.15 * param->n[2] + 0.85));
					else if (sierpinski_carpet(param->x[2] * v[0] / v[2] + param->ref[0],
						param->x[2] * v[1] / v[2], param->x[2], param))
						store_pixel(param, i, j, 0x000000FF * (0.15 * param->n[0] + 0.85));
					else if (sierpinski_carpet(param->x[2] * v[0] / v[2],
						param->x[2] * v[1] / v[2] + param->ref[1], param->x[2], param))
						store_pixel(param, i, j, 0x000000FF * (0.15 * param->n[1] + 0.85));
					a = 1;
				}
				param->x[2] += param->x[3] / (double)SI_LVL;
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
			(param.n = (double*)malloc(sizeof(double) * 3)) &&
			(param.x = (double*)malloc(sizeof(double) * 4)) &&
			(param.x_init = (double*)malloc(sizeof(double) * 3)) &&
			(param.ref = (double*)malloc(sizeof(double) * 3)) &&
			(param.src = (double*)malloc(sizeof(double) * 3)))
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
