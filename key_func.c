/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:39 by aguemy            #+#    #+#             */
/*   Updated: 2017/02/27 22:02:41 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	mandelbrot_filler(*param);
		return (0);
}
