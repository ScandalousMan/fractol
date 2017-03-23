/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menger_components.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 16:27:29 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/23 16:31:01 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

t_param	param_init(void *mlx, void *win, void *img, char *addr)
{
	t_param	param;

	param.mlx = mlx;
	param.win = win;
	param.img = img;
	param.addr = addr;
	param.marg_i = HEIGHT / 2;
	param.marg_j = WIDTH / 2;
	param.zoom = 1;
	param.ratio = 4 / (double)(ft_min(HEIGHT, WIDTH));
	return (param);
}

int		sierpinski_algo(int si1, int si2, int si3)
{
	if (si1 < 0 || si2 < 0 || si3 < 0 || si1 > SI_LVL - 1 ||
		si2 > SI_LVL - 1 || si3 > SI_LVL - 1)
		return (0);
	while ((si1 > 0 && (si2 > 0 || si3 > 0)) || (si2 > 0 && si3 > 0))
	{
		if ((si1 % 3 == 1 && (si2 % 3 == 1 || si3 % 3 == 1)) ||
				(si2 % 3 == 1 && si3 % 3 == 1))
			return (0);
		si1 /= 3;
		si2 /= 3;
		si3 /= 3;
	}
	return (1);
}

int		sierpinski_carpet(double x, double y, double z, t_param *param)
{
	int	si1;
	int	si2;
	int	si3;
	int	i;

	i = 1;
	if (x >= param->x_init[0] + param->x[3] || x < param->x_init[0] ||
			y >= param->x_init[1] + param->x[3] || y < param->x_init[1] ||
			z >= param->x_init[2] + param->x[3] || z < param->x_init[2])
		return (0);
	return (sierpinski_algo((int)trunc((x - param->x_init[0]) / param->x[3] *
			(double)(SI_LVL - 1)), (int)trunc((y - param->x_init[1]) /
			param->x[3] * (double)(SI_LVL - 1)), (int)trunc((z -
			param->x_init[2]) / param->x[3] * (double)(SI_LVL - 1))));
}

char	*addr_init(void *img)
{
	char	*addr;
	int		detail[3];

	detail[0] = 4;
	detail[1] = WIDTH * 4;
	detail[2] = 0;
	addr = mlx_get_data_addr(img, &(detail[0]), &(detail[1]), &(detail[2]));
	ft_bzero(addr, HEIGHT * WIDTH * 4);
	return (addr);
}

void	store_pixel(t_param *param, int i, int j, int color)
{
	if (i >= 0 && i < HEIGHT && j >= 0 && j < WIDTH)
	{
		param->addr[(i * WIDTH + j) * 4 + 2] = (color) & 0xFF;
		param->addr[(i * WIDTH + j) * 4 + 1] = (color >> 8) & 0xFF;
		param->addr[(i * WIDTH + j) * 4 + 0] = (color >> 16) & 0xFF;
	}
}
