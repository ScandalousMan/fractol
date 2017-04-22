/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:46:04 by aguemy            #+#    #+#             */
/*   Updated: 2017/04/22 14:12:42 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot_iter(double x, double y, t_param *param)
{
	double	tmp;

	tmp = param->z[0];
	param->z[0] = param->z[0] * param->z[0] - param->z[1] * param->z[1] + x;
	param->z[1] = 2 * tmp * param->z[1] + y;
}

void	julia_exp_iter(double x, double y, t_param *param)
{
	double	tmp;

	tmp = param->z[0];
	param->z[0] = (param->z[0] * param->z[0] - param->z[1] * param->z[1]) *
		param->z[0] - param->z[1] * 2.0 * param->z[0] * param->z[1];
	param->z[1] = 2.0 * tmp * param->z[1] * tmp + param->z[1] *
		(tmp * tmp - param->z[1] * param->z[1]);
	tmp = exp(param->z[0]);
	param->z[0] = tmp * cos(param->z[1]) + x;
	param->z[1] = tmp * sin(param->z[1]) + y;
}

void	julia_cube_iter(double x, double y, t_param *param)
{
	double	tmp;

	tmp = param->z[0];
	param->z[0] = param->z[0] * (param->z[0] * param->z[0] - param->z[1] *
			param->z[1]) - 2.0 * param->z[1] * param->z[1] * param->z[0] + x;
	param->z[1] = param->z[1] * (tmp * tmp - param->z[1] * param->z[1]) +
			2 * tmp * tmp * param->z[1] + y;
}

void	julia_flower_iter(double x, double y, t_param *param)
{
	double	tmp;

	tmp = param->z[0];
	param->z[0] = exp(tmp) * cos(param->z[1]) * (tmp * tmp - param->z[1] *
			param->z[1]) - 2.0 * tmp * param->z[1] * exp(tmp) *
			sin(param->z[1]) + x;
	param->z[1] = exp(tmp) * sin(param->z[1]) * (tmp * tmp - param->z[1] *
			param->z[1]) + 2.0 * exp(tmp) * tmp * param->z[1] *
			cos(param->z[1]) + y;
}

void	burning_iter(double x, double y, t_param *param)
{
	double	tmp;

	tmp = param->z[0];
	param->z[0] = param->z[0] * param->z[0] - param->z[1] * param->z[1] + x;
	if ((param->z[1] = 2.0 * tmp * param->z[1]) < 0.0)
		param->z[1] = -1 * param->z[1];
	param->z[1] += y;
}
