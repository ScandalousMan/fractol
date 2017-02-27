/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:39 by aguemy            #+#    #+#             */
/*   Updated: 2017/02/27 21:13:50 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		my_key_func(int keycode, t_param *param)
{
	if (keycode == 53)
		exit(0);
	ft_bzero(param->addr, HEIGHT * WIDTH * 4);
	//lines_print(param->nodes, param->dim, *param);
	return (0);
}
