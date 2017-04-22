/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:39 by aguemy            #+#    #+#             */
/*   Updated: 2017/04/22 15:16:51 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clear_buddha_components(t_param *param)
{
	param->i = 0;
	while (param->i < HEIGHT || param->i < ITER_MAX)
	{
		if (param->i < HEIGHT)
			free(param->tab[param->i]);
		if (param->i < ITER_MAX)
			free(param->buff[param->i]);
		param->i++;
	}
	free(param->buff);
	free(param->tab);
}

void	end_program(t_param *param)
{
	free(param->addr);
	free(param->img);
	free(param->win);
	free(param->mlx);
	free(param->z);
	free(param->c);
	if (param->origin == 2)
		clear_buddha_components(param);
	free(param);
	exit(0);
}

int		my_key_func(int keycode, t_param *param)
{
	if (keycode == 12)
		param->zoom = param->zoom * ZOOM_PARAM;
	else if (keycode == 13)
		param->zoom = param->zoom / ZOOM_PARAM;
	else if (keycode == 126)
		param->marg_i += 10;
	else if (keycode == 125)
		param->marg_i -= 10;
	else if (keycode == 124)
		param->marg_j += 10;
	else if (keycode == 123)
		param->marg_j -= 10;
	else if (keycode == 0)
		color_wheel(param);
	else if (keycode == 53)
		end_program(param);
	ft_bzero(param->addr, HEIGHT * WIDTH * 4);
	generic_filler(param);
	return (0);
}
