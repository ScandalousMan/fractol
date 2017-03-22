/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbulb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 18:00:46 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/15 14:11:36 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
/*
double	second_level(double a, double b, double c)
{
	double	det;

	det = sqrt(b * b - 4.0 * a * c);
	if (a < 0.0)
	{
		a = -a;
		b = -b;
		c = -c;
	}
	if (a == 0.0 || (b * b - 4.0 * a * c < 0.0) || (b > det))
		return (-1.0);
	else if ((-b - det) <= 0.0)
		return ((-b + det) / 2.0 / a);
	else
		return ((-b - det) / 2.0 / a);
}

void	rt_filler(t_param *param)
{
	int		i;
	int		j;
	double	x[3]; // x est le vecteur allant de l'oeil au centre de la sphere
	double	y[3]; // y est le vecteur allant de l'oeil au centre de la sphere 2
	double	v[3]; // v est le vecteur lié au point (i, j)
	double	src[3];
	double	R;
	double	a;
	double	b;
	double	beta;

	i = 0;
	R = 5.0;
	b = -1.0;
	x[0] = 0.0;
	x[1] = 4.0;
	x[2] = 60.0;
	src[0] = 0.0;
	src[1] = 28.0;
	src[2] = 0.0;
	v[2] = 40.0; //focale : distance entre oeil et ecran
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			v[0] = ((double)i - (double)HEIGHT / 2.0) * 40.0 / (double)HEIGHT;
			v[1] = ((double)j - (double)WIDTH / 2.0) * 40.0 / (double)WIDTH;
			if ((a = second_level(v[0] * v[0] + v[1] * v[1] + v[2] * v[2],//condition si le point fait partie de l'ensemble et est visible :-)
				-2.0 * (v[0] * x[0] + v[1] * x[1] + v[2] * x[2]),
				x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - R * R)) >= 0)
			{
				b = ((src[0] - a * v[0]) * (a * v[0] - x[0]) + (src[1] - a * v[1]) * (a * v[1] - x[1]) + (src[2] - a * v[2]) * (a * v[2] - x[2])) /
						sqrt((src[0] - a * v[0]) * (src[0] - a * v[0]) + (src[1] - a * v[1]) * (src[1] - a * v[1]) +
						(src[2] - a * v[2]) * (src[2] - a * v[2])) / sqrt((a * v[0] - x[0]) * (a * v[0] - x[0]) + (a * v[1] - x[1]) * (a * v[1] - x[1]) +
						(a * v[2] - x[2]) * (a * v[2] - x[2]));
				if (b < 0.0)
					b = 0.0;
				store_pixel(param, i, j, 0x000000FF * (0.85 * b + 0.15));
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(param->mlx, param->win, param->img, 50, 50);
}*/

int		zoom_to_ratio2(double zoom)
{
	int		i;

	i = 1;
	if (zoom != 0.0)
	{
		zoom = 1.0 / zoom;
		while ((int)trunc(zoom) / 3 != 0)
		{
			i = i * 3;
			zoom = zoom / 3.0;
		}
	}
	return (i);
}

int		sierpinski_carpet2(int *z, t_param *param)
{
	z[0] = z[0] * (double)zoom_to_ratio2(param->zoom);
	z[1] = z[1] * (double)zoom_to_ratio2(param->zoom);
	while (z[0] > 0 && z[1] > 0)
	{
		if (z[0] % 3 == 1 && z[1] % 3 == 1)
			return (0);
		z[0] /= 3;
		z[1] /= 3;
	}
	return (1);
}

void	mandelbulb_filler(t_param *param)
{
	int		i;
	int		j;
	int		k;
	int		*z;

	i = 0;
	k = 0;
	if ((z = (int*)malloc(sizeof(int) * 3)))
	{
		while (i < HEIGHT)
		{
			j = 0;
			while (j < WIDTH)
			{
				z[0] = ((double)i - (double)param->marg_i + (double)HEIGHT / 2.0) * param->ratio * param->zoom / HEIGHT;
				z[1] = ((double)j - (double)param->marg_j + (double)WIDTH / 2.0) * param->ratio * param->zoom / WIDTH;
				z[2] = k * param->zoom / DEPTH;
				if (z[0] >= 0 &&
						z[0] < param->ratio &&
						z[1] >= 0 &&
						z[1] < param->ratio &&
						sierpinski_carpet2(z, param))
					store_pixel(param, i, j, 0x00FFFFFF);
				j++;
			}
			i++;
		}
	}
	mlx_put_image_to_window(param->mlx, param->win, param->img, 50, 50);
}

void	mandelbulb_starter(void)
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
	param.ratio = 9 * 3 * 3 * 3 * 3 * 3;
	param.zoom = 1;
	param.marg_j = WIDTH / 2;
	param.origin = 4;
	if ((param.z = (double*)malloc(sizeof(double) * 2)) && (param.c = (double*)malloc(sizeof(double) * 2)))
	{
		mandelbulb_filler(&param);
		mlx_hook(param.win, 2, 1L << 2, my_key_func, &param);
		mlx_mouse_hook(param.win, my_mouse_hook, &param);
		mlx_loop(param.mlx);
	}
}
