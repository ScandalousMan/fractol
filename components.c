/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:53 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/15 14:52:39 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		higher_than_two(double x, double y, double two)
{
	if ((x * x + y * y) < two * two)
		return (0);
	return (1);
}

int		rgb_color(unsigned char red, unsigned char green, unsigned char blue)
{
	int		rgb;

	rgb = (blue << 16) | (green << 8) | (red);
	return (rgb);
}

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
