/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot_components2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 16:28:59 by aguemy            #+#    #+#             */
/*   Updated: 2017/05/08 14:55:47 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ratio_transform(int x)
{
	return (log(1.0 + (double)x));
}

int		buddha_color(t_param *param)
{
	int		rgb;
	double	ratio;

	rgb = 0;
	ratio = (ratio_transform(param->tab[param->i][param->j]) /
			ratio_transform(param->max));
	if (param->tab[param->i][param->j] != 0 && param->max != 0)
		rgb = rgb_color((unsigned char)((param->col % 256 % 256 + 16) * ratio),
				(unsigned char)((param->col % 256 / 256 + 16) * ratio),
				(unsigned char)((param->col / 256 / 256 + 16) * ratio));
	return (rgb);
}
