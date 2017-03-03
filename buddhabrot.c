/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:24:57 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/03 19:08:38 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		buddha_color(int i, int j, t_param *param)
{
	int		rgb;

	rgb = 0;
	if (!(param->tab[i][j] == 0) && param->max != 0)
		rgb = rgb_color((unsigned char)trunc(sqrt((double)param->tab[i][j]) *
			RED / sqrt((double)param->max)),
			(unsigned char)trunc(sqrt((double)param->tab[i][j]) *
			GREEN / sqrt((double)param->max)),
			(unsigned char)trunc(sqrt((double)param->tab[i][j]) *
			BLUE / sqrt((double)param->max)));
	return (rgb);
}

void	tab_to_pixels(t_param *param)
{
	int		i;
	int		j;
	int		col;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
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
	while (i < depth - 1)
	{
		if ((int)trunc((SUP_BORN - param->buff[i][1]) * (double)WIDTH / 2.0 / SUP_BORN) > 0 &&
			(int)trunc((SUP_BORN - param->buff[i][1]) * (double)WIDTH / 2.0 / SUP_BORN) < WIDTH &&
			(int)trunc((SUP_BORN + param->buff[i][0]) * (double)HEIGHT / 2.0 / SUP_BORN) > 0 &&
			(int)trunc((SUP_BORN + param->buff[i][0]) * (double)HEIGHT / 2.0 / SUP_BORN) < HEIGHT &&
			((int)trunc((SUP_BORN - param->buff[i][1]) * (double)WIDTH / 2.0 / SUP_BORN) != WIDTH / 2.0 ||
			(int)trunc((SUP_BORN + param->buff[i][0]) * (double)HEIGHT / 2.0 / SUP_BORN) != HEIGHT / 2.0))
		{
			tmp = param->tab[(int)trunc((SUP_BORN + param->buff[i][0]) * (double)HEIGHT /
				2.0 / SUP_BORN)][(int)trunc((SUP_BORN - param->buff[i][1]) * (double)WIDTH / 2.0 / SUP_BORN)]++;
			if (tmp > param->max)
				param->max = tmp;
		}
		i++;
	}
}

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

double	**memory_buffer(void)
{
	int		i;
	double	**buff;

	i = 0;
	if (!(buff = (double**)malloc(sizeof(double*) * ITER_MAX)))
		return (NULL);
	while (i < ITER_MAX)
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
