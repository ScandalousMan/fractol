/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:14 by aguemy            #+#    #+#             */
/*   Updated: 2017/04/27 17:30:53 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <pthread.h>

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
	ft_putstr("- Julia_flower [Re(Z0) Im(Z0)]\n");
	return (0);
}

void	*fractal_lister_simple(void *str)
{
	if (!(ft_strcmp(str, "Mandelbrot")))
		mandelbrot_starter();
	else if (!(ft_strcmp(str, "Julia")))
		julia_starter(2, (char**)&str);
	else if (!(ft_strcmp(str, "Buddhabrot")))
		buddha_starter();
	else if (!(ft_strcmp(str, "Julia_exp")))
		julia_exp_starter(2, (char**)&str);
	else if (!(ft_strcmp(str, "Burning_ship")))
		burning_ship_starter();
	else if (!(ft_strcmp(str, "Julia_cube")))
		julia_cube_starter(2, (char**)&str);
	else if (!(ft_strcmp(str, "Julia_flower")))
		julia_flower_starter(2, (char**)&str);
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
		julia_starter(4, str);
	else if (!(ft_strcmp(str[1], "Julia_exp")))
		julia_exp_starter(4, str);
	else if (!(ft_strcmp(str[1], "Julia_cube")))
		julia_cube_starter(4, str);
	else if (!(ft_strcmp(str[1], "Julia_flower")))
		julia_flower_starter(4, str);
	else
		return (error_input());
	return (1);
}

int		check_errors(int argc, char **argv)
{
	int			i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "Mandelbrot") &&
				ft_strcmp(argv[i], "Julia")  &&
				ft_strcmp(argv[i], "Buddhabrot") &&
				ft_strcmp(argv[i], "Julia_exp") &&
				ft_strcmp(argv[i], "Burning_ship") &&
				ft_strcmp(argv[i], "Julia_cube") &&
				ft_strcmp(argv[i], "Julia_flower"))
			return (0);
		i++;
	}
	return (1);
}

int		main(int argc, char **argv)
{
	pthread_t	*threads;

	if (argc == 2)
		(fractal_lister_simple(argv[1]));
	else if (argc == 3)
	{
		if (!(check_errors(argc, argv)))
		{
			error_input();
			return (0);
		}
		if (!(threads = (pthread_t*)malloc(sizeof(pthread_t) * 2)))
			return (0);
		pthread_create(threads, NULL, &fractal_lister_simple, argv[1]);
		pthread_create(threads + 1, NULL, &fractal_lister_simple, argv[2]);
		pthread_join(threads[0], NULL);
		pthread_join(threads[1], NULL);
		return (1);
	}
	else if (argc == 4)
		return (fractal_lister_enriched(argv));
	else
		error_input();
	return (0);
}
