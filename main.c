/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:14 by aguemy            #+#    #+#             */
/*   Updated: 2017/04/21 15:20:36 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		error_input(void)
{
	ft_putstr("usage: ./fractol fractal_name [options] :\n");
	ft_putstr("- Mandelbrot\n- Julia [Re(Z0) Im(Z0)]\n- Buddhabrot\n");
	ft_putstr("- Julia_exp [Re(Z0) Im(Z0)]\n");
	return (0);
}

int		fractal_lister(int argc, char **str)
{
	if (!(ft_strcmp(str[1], "Mandelbrot")) && argc == 2)
		mandelbrot_starter();
	else if (!(ft_strcmp(str[1], "Julia")) && (argc == 2 || argc == 4))
		julia_starter(argc, str);
	else if (!(ft_strcmp(str[1], "Buddhabrot")) && argc == 2)
		buddha_starter();
	else if (!(ft_strcmp(str[1], "Julia_exp")) && (argc == 2 || argc == 4))
		julia_exp_starter(argc, str);
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
