/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:30:25 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/10 17:59:10 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		my_mouse_hook(int button, int x, int y, t_param *param)
{
	x -= 50;
	y -= 50;
	if (button == 5)
	{
		param->zoom = param->zoom * ZOOM_PARAM;
		param->marg_j = (double)x + ((double)param->marg_j - (double)x) / ZOOM_PARAM;
		param->marg_i = (double)y + ((double)param->marg_i - (double)y) / ZOOM_PARAM;
	}
	if (button == 4)
	{
		param->zoom = param->zoom / ZOOM_PARAM;
		param->marg_j = (double)x + ZOOM_PARAM * ((double)param->marg_j - (double)x);
		param->marg_i = (double)y + ZOOM_PARAM * ((double)param->marg_i - (double)y);
	}
	ft_bzero(param->addr, HEIGHT * WIDTH * 4);
	back_to_function(param);
	return (0);
}
