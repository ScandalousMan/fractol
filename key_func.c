/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:39 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/06 19:51:58 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	back_to_function(t_param *param)
{
	if (param->origin == 0)
		mandelbrot_filler(param);
	else if (param->origin == 1)
		julia_filler(param);
	else if (param->origin == 2)
		buddhabrot_filler(param);
	else if (param->origin == 3)
		julia_exp_filler(param);
}

int		my_key_func(int keycode, t_param *param)
{
	if (keycode == 12)
		param->zoom = param->zoom * 1.1;
	else if (keycode == 13)
		param->zoom = param->zoom * 0.9;
	else if (keycode == 126)
		param->marg_i += 10;
	else if (keycode == 125)
		param->marg_i -= 10;
	else if (keycode == 124)
		param->marg_j += 10;
	else if (keycode == 123)
		param->marg_j -= 10;
	else if (keycode == 53)
		exit(0);
	ft_bzero(param->addr, HEIGHT * WIDTH * 4);
	back_to_function(param);
	return (0);
}
