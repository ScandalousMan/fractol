/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:57:14 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/24 11:28:53 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		absolute(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

static int		alloc_me(char **str, int n)
{
	int		i;

	i = 0;
	if (n < 0)
		i = 1;
	while (n < -9 || n > 9)
	{
		n = n / 10;
		i++;
	}
	if (!(*str = (char*)malloc(sizeof(char) * (i + 2))))
		return (0);
	(*str)[i + 1] = '\0';
	return (i + 1);
}

char			*ft_itoa(int n)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!(j = alloc_me(&str, n)))
		return (NULL);
	while (n < -9 || n > 9)
	{
		str[j - 1] = absolute(n % 10) + 48;
		n = n / 10;
		j--;
	}
	str[j - 1] = absolute(n % 10) + 48;
	if (n < 0)
		str[0] = '-';
	return (str);
}
