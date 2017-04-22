/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:14 by aguemy            #+#    #+#             */
/*   Updated: 2017/04/22 14:05:21 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	generic_filler(t_param *param)
{
	param->i = 0;
	param->count = 0;
	while (param->i < HEIGHT)
	{
		param->j = 0;
		while (param->j < WIDTH)
		{
			param->algo(param);
			param->j++;
		}
		param->i++;
	}
	if (param->origin == 2)
		tab_to_pixels(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img, 50, 50);
}

int		error_input(void)
{
	ft_putstr("usage: ./fractol fractal_name [options] :\n");
	ft_putstr("- Mandelbrot\n- Julia [Re(Z0) Im(Z0)]\n- Buddhabrot\n");
	ft_putstr("- Julia_exp [Re(Z0) Im(Z0)]\n- Burning_ship\n");
	ft_putstr("- Julia_cube [Re(Z0) Im(Z0)]\n");
	ft_putstr("- Julia_sinh [Re(Z0) Im(Z0)]\n");
	return (0);
}

int		fractal_lister(int argc, char **str)
{
	if (argc == 2 && !(ft_strcmp(str[1], "Mandelbrot")))
		mandelbrot_starter();
	else if ((argc == 2 || argc == 4) && !(ft_strcmp(str[1], "Julia")))
		julia_starter(argc, str);
	else if (argc == 2 && !(ft_strcmp(str[1], "Buddhabrot")))
		buddha_starter();
	else if ((argc == 2 || argc == 4) && !(ft_strcmp(str[1], "Julia_exp")))
		julia_exp_starter(argc, str);
	else if (argc == 2 && !(ft_strcmp(str[1], "Burning_ship")))
		burning_ship_starter();
	else if ((argc == 2 || argc == 4) && !(ft_strcmp(str[1], "Julia_cube")))
		julia_cube_starter(argc, str);
	else if ((argc == 2 || argc == 4) && !(ft_strcmp(str[1], "Julia_sinh")))
		julia_flower_starter(argc, str);
	else
		return (error_input());
	return (1);
}

int		main(int argc, char **argv)
{
	if (argc < 2)
		return (error_input());
	return (fractal_lister(argc, argv));
}
