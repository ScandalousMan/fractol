/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:14 by aguemy            #+#    #+#             */
/*   Updated: 2017/02/28 16:20:17 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		error_input(void)
{
	ft_putstr("usage: ./fractol fractal_name with fractal name among:\n");
	ft_putstr("- Julia\n- Mandelbrot\n");
	return (0);
}

int		fractal_lister(char *str)
{
	if (!(ft_strcmp(str, "Mandelbrot")))
		mandelbrot_starter();
	else if (!(ft_strcmp(str, "Julia")))
		julia_starter();
	else if (!(ft_strcmp(str, "Buddhabrot")))
		buddha_starter();
	else
		return (error_input());
	return (1);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		return (error_input());
	return (fractal_lister(argv[1]));
}
