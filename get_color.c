/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:01:32 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/05 00:44:25 by jgoldste         ###   ########.fr       */
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

int	get_color(t_fdf *map, char **str_split, int x, int y)
{
	char	**num_color;
	
	num_color = ft_split(str_split[x], ',');
	if (!num_color)
		return (1);
	if (array_len(num_color) > 2)
		return (-1);
	if (check_digit(num_color[0]))
		return (-1);
	map->z[y][x] = ft_atoi(num_color[0]);
	if (!map->z[y][x])
		map->color[y][x] = 0xffffff;
	else
		map->color[y][x] = 0xff0000;
	// if (!num_color[1])
	// 	map->color[y][x] = 0xffffff;
	// else
	// 	map->color[y][x] = 0xff0000;
	free_array((void **)num_color);
	return (0);
}