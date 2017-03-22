/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 11:24:01 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/16 11:24:03 by aguemy           ###   ########.fr       */
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
			if ((a = second_level(v[0] * v[0] + v[1] * v[1] + v[2] * v[2],
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
	if ((param.z = (double*)malloc(sizeof(double) * 2)) && (param.c = (double*)malloc(sizeof(double) * 2)))
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
