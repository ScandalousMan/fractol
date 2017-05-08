/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:30:25 by aguemy            #+#    #+#             */
/*   Updated: 2017/05/08 15:23:55 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		my_pointer_motion(int x, int y, t_param *param)
{
	if (param->mouse_param_modifier == 1)
	{
		x -= 50;
		y -= 50;
		param->c[0] = ((double)x - (double)HEIGHT / 2.0) / (double)HEIGHT * 4.0;
		param->c[1] = ((double)y - (double)WIDTH / 2.0) / (double)WIDTH * 4.0;
		ft_bzero(param->addr, HEIGHT * WIDTH * 4);
		generic_filler(param);
		return (1);
	}
	return (0);
}

void	my_mouse_dezoom(int x, int y, t_param *param)
{
	if (param->zoom < ZOOM_MAX)
	{
		param->zoom = param->zoom * ZOOM_PARAM;
		param->marg_j = (double)x +
			((double)param->marg_j - (double)x) / ZOOM_PARAM;
		param->marg_i = (double)y +
			((double)param->marg_i - (double)y) / ZOOM_PARAM;
	}
}

void	my_mouse_zoom(int x, int y, t_param *param)
{
	if (param->zoom > 1.0 / ZOOM_MAX)
	{
		param->zoom = param->zoom / ZOOM_PARAM;
		param->marg_j = (double)x +
			ZOOM_PARAM * ((double)param->marg_j - (double)x);
		param->marg_i = (double)y +
			ZOOM_PARAM * ((double)param->marg_i - (double)y);
	}
}

int		my_mouse_hook(int button, int x, int y, t_param *param)
{
	x -= 50;
	y -= 50;
	if (button == 5)
		my_mouse_dezoom(x, y, param);
	else if (button == 4)
		my_mouse_zoom(x, y, param);
	else
		return (0);
	ft_bzero(param->addr, HEIGHT * WIDTH * 4);
	generic_filler(param);
	return (1);
}
