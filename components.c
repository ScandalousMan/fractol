/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:53 by aguemy            #+#    #+#             */
/*   Updated: 2017/02/27 21:34:04 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_param	param_init(void *mlx, void *win, void *img, char *addr)
{
	t_param	param;

	param.mlx = mlx;
	param.win = win;
	param.img = img;
	param.addr = addr;
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

void	store_pixel(t_param param, int i, int j, int color)
{
	param.addr[(i * WIDTH + j) * 4 + 2] = color / 256 / 256;
	param.addr[(i * WIDTH + j) * 4 + 1] = color % (256 * 256) / 256;
	param.addr[(i * WIDTH + j) * 4 + 0] = color % 256;
}
