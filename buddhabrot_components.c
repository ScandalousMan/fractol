/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot_components.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 21:20:18 by aguemy            #+#    #+#             */
/*   Updated: 2017/05/08 14:58:15 by aguemy           ###   ########.fr       */
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
		if ((int)((param->buff[param->k][1] + SUP_BORN) * (double)HEIGHT / 2.0 /
			SUP_BORN / param->zoom) + param->marg_i > 0 &&
			(int)((param->buff[param->k][1] + SUP_BORN) * (double)HEIGHT / 2.0 /
			SUP_BORN / param->zoom) + param->marg_i < HEIGHT &&
			(int)((param->buff[param->k][0] + SUP_BORN) * (double)WIDTH / 2.0 /
			SUP_BORN / param->zoom) + param->marg_j > 0 &&
			(int)((param->buff[param->k][0] + SUP_BORN) * (double)WIDTH / 2.0 /
			SUP_BORN / param->zoom) + param->marg_j < WIDTH &&
			((int)((param->buff[param->k][1] + SUP_BORN) * (double)HEIGHT /
			2.0 / SUP_BORN / param->zoom) + param->marg_i != HEIGHT / 2.0 ||
			(int)((param->buff[param->k][0] + SUP_BORN) * (double)WIDTH /
			2.0 / SUP_BORN / param->zoom) + param->marg_j != WIDTH / 2.0))
			param->tmp = param->tab[(int)((param->buff[param->k][1] +
				SUP_BORN) * (double)HEIGHT / 2.0 / SUP_BORN / param->zoom) +
				param->marg_i][(int)((param->buff[param->k][0] + SUP_BORN) *
				(double)WIDTH / 2.0 / SUP_BORN / param->zoom) +
				param->marg_j]++;
		if (param->tmp > param->max)
			param->max = param->tmp;
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
