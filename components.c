/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:53 by aguemy            #+#    #+#             */
/*   Updated: 2017/04/30 15:12:52 by aguemy           ###   ########.fr       */
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
	int				rgb;

	rgb = (blue << 16) | (green << 8) | (red);
	return (rgb);
}

void	color_wheel(t_param *param)
{
	param->col = rgb_color((unsigned char)((param->col % 256 % 256 + 16) % 256),
			(unsigned char)((param->col % 256 / 256 + 16) % 256),
			(unsigned char)((param->col / 256 / 256 + 16) % 256));
}

char	*addr_init(void *img)
{
	char			*addr;
	int				*detail;

	if (!(detail = (int*)malloc(sizeof(int) * 3)))
		return (NULL);
	detail[0] = 4;
	detail[1] = WIDTH * 4;
	detail[2] = 0;
	addr = mlx_get_data_addr(img, &(detail[0]), &(detail[1]), &(detail[2]));
	ft_bzero(addr, HEIGHT * WIDTH * 4);
	free(detail);
	return (addr);
}

void	store_pixel(t_param *param, int color)
{
	if (param->i >= 0 && param->i < HEIGHT && param->j >= 0 && param->j < WIDTH)
	{
		param->addr[(param->i * WIDTH + param->j) * 4 +
			2] = (color) & 0xFF;
		param->addr[(param->i * WIDTH + param->j) * 4 +
			1] = (color >> 8) & 0xFF;
		param->addr[(param->i * WIDTH + param->j) * 4 +
			0] = (color >> 16) & 0xFF;
	}
}
