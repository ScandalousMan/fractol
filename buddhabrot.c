/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:24:57 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/02 16:48:29 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		*buddha_color(int i, int j, t_param *param)
{
	int		*rgb;

	if (!(rgb = (int*)malloc(sizeof(int) * 3)))
		return (NULL);
	if (param->tab[i][j] == 0)
	{
		rgb[0] = 0;
		rgb[1] = 0;
		rgb[2] = 0;
	}
	else if (param->max != 0)
	{
		rgb[0] = 128 + trunc(sqrt((double)param->tab[i][j]) / sqrt((double)param->max) * 127);
		rgb[1] = rgb[0];
		rgb[2] = rgb[0];
		return (rgb);
	}
	return (NULL);
}

void	tab_to_pixels(t_param *param)
{
	int		i;
	int		j;
	int		*col;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
//			store_pixel(param, i, j, (int)((double)0x00FFFFFF *
//				((double)param->tab[i][j] / (double)param->max)));
			if ((col = buddha_color(i, j, param)))
				store_pixel(param, i, j, col);
			j++;
		}
		i++;
	}
}

void	tab_update(t_param *param, int depth)
{
	int		i;
	int		tmp;

	i = 0;
	while (i < depth)
	{
		if ((int)round((2.0 - param->buff[depth][1]) * (double)HEIGHT / 4.0) >= 0 &&
			(int)round((2.0 - param->buff[depth][1]) * (double)HEIGHT / 4.0) < HEIGHT &&
			(int)round((2.0 + param->buff[depth][0]) * (double)WIDTH / 4.0) >= 0 &&
			(int)round((2.0 + param->buff[depth][0]) * (double)WIDTH / 4.0) < WIDTH &&
			((int)round((2.0 - param->buff[depth][1]) * (double)HEIGHT / 4.0) != HEIGHT / 2.0 ||
			(int)round((2.0 + param->buff[depth][0]) * (double)WIDTH / 4.0) != WIDTH / 2.0))
		{
			tmp = param->tab[(int)round((2.0 - param->buff[depth][1]) * (double)(HEIGHT) /
				4.0)][(int)round((param->buff[depth][0] + 2.0) * (double)WIDTH / 4.0)]++;
			if (tmp > param->max)
				param->max = tmp;
		}
		i++;
	}
}

void	tab_display(int **tab)
{
	int		i;
	int		j;

	i = HEIGHT / 2;
	ft_putstr("Check tab 0\n");
	j = 0;
	while (j < WIDTH)
	{
		ft_putnbr(tab[i][j]);
		ft_putstr(",");
		j++;
	}
	ft_putstr("\n");
}
/*
void	tab_update_bis(t_param *param)
{
	int		tmp;

	if ((int)round((2.0 - param->z[1]) * (double)HEIGHT / 4.0) >= 0 &&
		(int)round((2.0 - param->z[1]) * (double)HEIGHT / 4.0) < HEIGHT &&
		(int)round((2.0 + param->z[0]) * (double)WIDTH / 4.0) >= 0 &&
		(int)round((2.0 + param->z[0]) * (double)WIDTH / 4.0) < WIDTH)
	{
		tmp = param->tab[(int)round((2.0 - param->z[1]) * (double)(HEIGHT) /
			4.0)][(int)round((param->z[0] + 2.0) * (double)WIDTH / 4.0)]++;
		if (tmp > param->max)
			param->max = tmp;
	}
}*/

void	buddhabrot_filler(t_param *param)
{
	int		depth;
	int		i;
	int		j;
	int		flag;

	i = 0;
	while (i < RATIO)
	{
		j = 0;
		while (j < RATIO)
		{
			flag = 1;
			depth = 0;
			param->z[0] = 0.0;
			param->z[1] = 0.0;
			while (param->buff && depth < DEPTH && flag)
			{
				if (depth > 0)
				{
					param->buff[depth - 1][0] = param->z[0];
					param->buff[depth - 1][1] = param->z[1];
				}
				mandelbrot_iter(((double)j - RATIO / 2.0) * 4.0 / (double)RATIO, (RATIO / 2.0 - (double)i) * 4.0 / (double)RATIO, param);
				if ((higher_than_two(param->z[0], param->z[1])))
				{
					tab_update(param, depth);
					flag = 0;
				}
				depth++;
			}
			j++;
		}
		i++;
	}
	ft_putstr("Tableau rempli\n");
	tab_to_pixels(param);
	ft_putstr("Image remplie\n");
	mlx_put_image_to_window(param->mlx, param->win, param->img, 50, 50);
}

double	**memory_buffer(void)
{
	int		i;
	double	**buff;

	i = 0;
	if (!(buff = (double**)malloc(sizeof(double*) * DEPTH)))
		return (NULL);
	while (i < DEPTH)
	{
		if (!(buff[i] = (double*)malloc(sizeof(double) * 2)))
			return (NULL);
		i++;
	}
	return (buff);
}

int		**tab_init(void)
{
	int		i;
	int		j;
	int		**tab;

	i = 0;
	if (!(tab = (int**)malloc(sizeof(int*) * HEIGHT)))
		return (NULL);
	while (i < HEIGHT)
	{
		j = 0;
		if (!(tab[i] = (int*)malloc(sizeof(int) * WIDTH)))
			return (NULL);
		while (j < WIDTH)
		{
			tab[i][j] = 0;
			j++;
		}
		i++;
	}
	return (tab);
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
	param.buff = memory_buffer();
	if ((param.z = (double*)malloc(sizeof(double) * 2)))
	{
		buddhabrot_filler(&param);
/*		tab_update2(&param);
		tab_to_pixels(&param);
		mlx_put_image_to_window(param.mlx, param.win, param.img, 50, 50);*/
		mlx_hook(param.win, 2, 1L << 2, my_key_func, &param);
		mlx_loop(param.mlx);
	}
}
