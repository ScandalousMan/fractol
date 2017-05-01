/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:14 by aguemy            #+#    #+#             */
/*   Updated: 2017/05/01 16:30:41 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	generic_filler(t_param *param)
{
	param->i = 0;
	param->count = 0;
	if (param->origin == 2)
		clear_tab(param);
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
	ft_putstr("- Julia_flower [Re(Z0) Im(Z0)]\n");
	return (0);
}

void	*fractal_lister_simple(void *str, t_mlx *multi)
{
	if (!(ft_strcmp(str, "Mandelbrot")))
		mandelbrot_starter(multi);
	else if (!(ft_strcmp(str, "Julia")))
		julia_starter(2, (char**)&str, multi);
	else if (!(ft_strcmp(str, "Buddhabrot")))
		buddha_starter(multi);
	else if (!(ft_strcmp(str, "Julia_exp")))
		julia_exp_starter(2, (char**)&str, multi);
	else if (!(ft_strcmp(str, "Burning_ship")))
		burning_ship_starter(multi);
	else if (!(ft_strcmp(str, "Julia_cube")))
		julia_cube_starter(2, (char**)&str, multi);
	else if (!(ft_strcmp(str, "Julia_flower")))
		julia_flower_starter(2, (char**)&str, multi);
	else
	{
		error_input();
		return (NULL);
	}
	return ((void*)str);
}

int		fractal_lister_enriched(char **str)
{
	if (!(ft_strcmp(str[1], "Julia")))
		julia_starter(4, str, NULL);
	else if (!(ft_strcmp(str[1], "Julia_exp")))
		julia_exp_starter(4, str, NULL);
	else if (!(ft_strcmp(str[1], "Julia_cube")))
		julia_cube_starter(4, str, NULL);
	else if (!(ft_strcmp(str[1], "Julia_flower")))
		julia_flower_starter(4, str, NULL);
	else
		return (error_input());
	return (1);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
		fractal_lister_simple(argv[1], NULL);
	else if (argc == 4)
		return (fractal_lister_enriched(argv));
	else
		error_input();
	return (0);
}
