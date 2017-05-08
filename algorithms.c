/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:38:20 by aguemy            #+#    #+#             */
/*   Updated: 2017/05/08 14:56:09 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot_algo(t_param *param)
{
	param->flag = 1;
	param->depth = 0;
	param->z[0] = 0;
	param->z[1] = 0;
	while (param->depth < ITER_MAX_MANDELBROT && param->flag)
	{
		param->iter(((double)(param->j) - (double)param->marg_j) /
			(double)WIDTH * 4.0 * param->zoom, ((double)(param->i) -
			(double)param->marg_i) / (double)HEIGHT * 4.0 *
			param->zoom, param);
		if (higher_than_two(param->z[0], param->z[1], 2.0))
		{
			store_pixel(param, (double)(param->depth) /
				(double)ITER_MAX_MANDELBROT * param->col);
			param->flag = 0;
		}
		param->depth++;
	}
}

void	julia_algo(t_param *param)
{
	param->flag = 1;
	param->depth = 0;
	param->z[0] = ((double)(param->j) - (double)param->marg_j) /
		(double)WIDTH * SUP_BORN * 2.0 * param->zoom;
	param->z[1] = ((double)param->marg_i - (double)(param->i)) /
		(double)HEIGHT * SUP_BORN * 2.0 * param->zoom;
	while (param->depth < ITER_MAX_JULIA && param->flag)
	{
		param->iter(param->c[0], param->c[1], param);
		if (higher_than_two(param->z[0], param->z[1], 2.0))
		{
			store_pixel(param, (double)(param->depth) /
				(double)ITER_MAX_JULIA * param->col);
			param->flag = 0;
		}
		param->depth++;
	}
}

void	buddhabrot_algo(t_param *param)
{
	param->depth = 0;
	param->z[0] = 0.0;
	param->z[1] = 0.0;
	while (param->buff && param->depth < ITER_MAX &&
			!(higher_than_two(param->z[0], param->z[1], DIVERGE)))
	{
		param->iter(((double)(param->j) - (double)WIDTH / 2.0) /
			(double)WIDTH * 2.0 * SUP_BORN * param->zoom, ((double)(param->i) -
			(double)HEIGHT / 2.0) / (double)HEIGHT * 2.0 * SUP_BORN *
			param->zoom, param);
		param->buff[param->depth][0] = -1.0 * param->z[1];
		param->buff[param->depth][1] = param->z[0];
		param->depth++;
	}
	if ((higher_than_two(param->z[0], param->z[1], DIVERGE)) &&
			param->depth > ITER_MIN)
	{
		tab_update(param);
		param->count++;
	}
}
