/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot_components.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 21:20:18 by aguemy            #+#    #+#             */
/*   Updated: 2017/05/01 18:45:37 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clear_tab(t_param *param)
{
	int		i;

	i = 0;
	param->max = 0;
	param->tmp = -1;
	while (i < HEIGHT)
	{
		ft_bzero(param->tab[i], WIDTH * 4);
		i++;
	}
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

		if ((int)trunc((param->marg_j - param->buff[param->k][1]) *
					(double)WIDTH / 2.0 / SUP_BORN / param->zoom) > 0 &&
			(int)trunc((param->marg_j - param->buff[param->k][1]) *
				(double)WIDTH / 2.0 / SUP_BORN / param->zoom) < WIDTH &&
			(int)trunc((param->marg_i + param->buff[param->k][0]) *
				(double)HEIGHT / 2.0 / SUP_BORN / param->zoom) > 0 &&
			(int)trunc((param->marg_i + param->buff[param->k][0]) *
				(double)HEIGHT / 2.0 / SUP_BORN / param->zoom) < HEIGHT &&
			((int)trunc((param->marg_j - param->buff[param->k][1]) *
				(double)WIDTH / 2.0 / SUP_BORN / param->zoom) != WIDTH / 2.0 ||
			(int)trunc((param->marg_i + param->buff[param->k][0]) *
				(double)HEIGHT / 2.0 / SUP_BORN / param->zoom) != HEIGHT / 2.0))
		{
			param->tmp = param->tab[(int)trunc((param->marg_i + param->buff[param->k]
				[0]) * (double)HEIGHT / 2.0 / SUP_BORN / param->zoom)]
				[(int)trunc((param->marg_j - param->buff[param->k][1]) *
				(double)WIDTH / 2.0 / SUP_BORN / param->zoom)]++;
/*
		if ((int)trunc((SUP_BORN - param->buff[param->k][1]) *
					(double)WIDTH / 2.0 / SUP_BORN / param->zoom) > 0 &&
			(int)trunc((SUP_BORN - param->buff[param->k][1]) *
				(double)WIDTH / 2.0 / SUP_BORN / param->zoom) < WIDTH &&
			(int)trunc((SUP_BORN + param->buff[param->k][0]) *
				(double)HEIGHT / 2.0 / SUP_BORN / param->zoom) > 0 &&
			(int)trunc((SUP_BORN + param->buff[param->k][0]) *
				(double)HEIGHT / 2.0 / SUP_BORN / param->zoom) < HEIGHT &&
			((int)trunc((SUP_BORN - param->buff[param->k][1]) *
				(double)WIDTH / 2.0 / SUP_BORN / param->zoom) != WIDTH / 2.0 ||
			(int)trunc((SUP_BORN + param->buff[param->k][0]) *
				(double)HEIGHT / 2.0 / SUP_BORN / param->zoom) != HEIGHT / 2.0))
		{
			param->tmp = param->tab[(int)trunc((SUP_BORN + param->buff[param->k]
				[0]) * (double)HEIGHT / 2.0 / SUP_BORN / param->zoom)]
				[(int)trunc((SUP_BORN - param->buff[param->k][1]) *
				(double)WIDTH / 2.0 / SUP_BORN / param->zoom)]++;
*/			if (param->tmp > param->max)
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
