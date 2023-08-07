/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:01:32 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/05 18:44:59 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	get_color(char *hex, int i)
{
	int	hex_num;
	int	hex_read;

	hex_num = 0;
	hex_read = 0;
	if (hex[i++] != '0')
		return (-1);
	if (ft_toupper(hex[i++]) != 'X')
		return (-1);
	while (hex[i])
	{
		if (i >= 8)
			return (-1);
		hex_read = check_hex(ft_toupper(hex[i]), BASE16);
		if (hex_read >= 0)
			hex_num = hex_num * 16 + hex_read;
		else
			return (-1);
		i++;
	}
	if (i == 2)
		return (-1);
	return (hex_num);
}

static void	set_z_min_max(t_fdf *map, int x, int y)
{
	if (x == 0 && y == 0)
	{
		map->z_min = map->matrix[y][x].z;
		map->z_max = map->matrix[y][x].z;
	}
	else
	{
		map->z_min = ft_min(map->z_min, map->matrix[y][x].z);
		map->z_max = ft_max(map->z_max, map->matrix[y][x].z);
	}
}

int	fill_values(t_fdf *map, char **str_split, int x, int y)
{
	char	**num_color;

	num_color = ft_split(str_split[x], ',');
	if (!num_color)
		return (error_map_return((void **)num_color, -1));
	if (array_len(num_color) > 2 || check_digit(num_color[0]))
		return (error_map_return((void **)num_color, 1));
	map->matrix[y][x].x = x - map->width / 2;
	map->matrix[y][x].y = y - map->height / 2;
	map->matrix[y][x].z = ft_atoi(num_color[0]);
	map->matrix[y][x].z_default = map->matrix[y][x].z;
	set_z_min_max(map, x, y);
	if (num_color[1])
	{
		map->matrix[y][x].color = get_color(num_color[1], 0);
		if (map->matrix[y][x].color == -1)
			return (error_map_return((void **)num_color, 1));
	}
	else
		map->matrix[y][x].color = COLOR_MAIN;
	map->matrix[y][x].color_default = map->matrix[y][x].color;
	free_array((void **)num_color);
	return (0);
}
