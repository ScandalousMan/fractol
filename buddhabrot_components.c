/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot_components.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 21:20:18 by aguemy            #+#    #+#             */
/*   Updated: 2017/04/21 18:57:21 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		buddha_color(t_param *param)
{
	int		rgb;

	rgb = 0;
	if (!(param->tab[param->i][param->j] == 0) && param->max != 0)
		rgb = rgb_color((unsigned char)trunc(sqrt((
			double)param->tab[param->i][param->j]) *
			RED / sqrt((double)param->max)),
			(unsigned char)trunc(sqrt((double)param->tab[param->i][param->j]) *
			GREEN / sqrt((double)param->max)),
			(unsigned char)trunc(sqrt((double)param->tab[param->i][param->j]) *
			BLUE / sqrt((double)param->max)));
	return (rgb);
}

void	tab_to_pixels(t_param *param)
{
	int		col;

	param->i = 0;
	while (param->i < HEIGHT)
	{
		param->j = 0;
		while (param->j < WIDTH)
		{
			if ((col = buddha_color(param)))
				store_pixel(param, col);
			param->j++;
		}
		param->i++;
	}
}

void	tab_update(t_param *param)
{
	param->k = 0;
	while (param->k < param->depth - 1)
	{
		if ((int)trunc((SUP_BORN - param->buff[param->k][1]) *
					(double)WIDTH / 2.0 / SUP_BORN) > 0 &&
			(int)trunc((SUP_BORN - param->buff[param->k][1]) *
				(double)WIDTH / 2.0 / SUP_BORN) < WIDTH &&
			(int)trunc((SUP_BORN + param->buff[param->k][0]) *
				(double)HEIGHT / 2.0 / SUP_BORN) > 0 &&
			(int)trunc((SUP_BORN + param->buff[param->k][0]) *
				(double)HEIGHT / 2.0 / SUP_BORN) < HEIGHT &&
			((int)trunc((SUP_BORN - param->buff[param->k][1]) *
				(double)WIDTH / 2.0 / SUP_BORN) != WIDTH / 2.0 ||
			(int)trunc((SUP_BORN + param->buff[param->k][0]) *
				(double)HEIGHT / 2.0 / SUP_BORN) != HEIGHT / 2.0))
		{
			param->tmp = param->tab[(int)trunc((SUP_BORN + param->buff[param->k]
				[0]) * (double)HEIGHT / 2.0 / SUP_BORN)][(int)trunc((SUP_BORN -
				param->buff[param->k][1]) * (double)WIDTH / 2.0 / SUP_BORN)]++;
			if (param->tmp > param->max)
				param->max = param->tmp;
		}
		param->k++;
	}
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
