/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 19:28:42 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/10 19:33:46 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

int	check_hex(char hex, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (hex == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	check_digit(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
		{
			if ((arg[i] != '-' && arg[i] != '+') || i != 0)
				return (1);
			if ((arg[0] == '-' || arg[0] == '+') && ft_strlen(arg) == 1)
				return (1);
		}
	}
	return (0);
}
