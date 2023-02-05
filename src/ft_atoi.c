/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 00:18:48 by lubov             #+#    #+#             */
/*   Updated: 2022/02/02 01:32:20 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isnumb(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	ft_isspace(int c)
{
	if (c == 32 || c == 9 || c == 10 || c == 11 \
		|| c == 12 || c == 13)
		return (1);
	return (0);
}

double	ft_parce_dr(char *str)
{
	int		k;
	int		dr;
	double	res;

	k = 0;
	dr = 0;
	str++;
	while (ft_isdigit(*str))
	{
		dr = (dr * 10) + (int)*str - '0';
		str++;
		k++;
	}
	if (*str != '\0')
		return (-1.0);
	res = (double)dr / pow(10., k);
	return (res);
}

double	ft_s_to_d(char *str)
{
	size_t		i;
	int			num;
	int			minus;

	i = 0;
	num = 0;
	minus = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (int)str[i] - '0';
		i++;
	}
	if (str[i] == '\0')
		return ((double)(num * minus));
	if (str[i] != '.' || (ft_parce_dr(str + i) == 1))
		return (0);
	return ((double)(minus * (num + ft_parce_dr(str + i))));
}
