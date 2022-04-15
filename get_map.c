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

int	fill_values(t_fdf *map, char **str_split, int x, int y)
{
	char	**num_color;

	num_color = ft_split(str_split[x], ',');
	if (!num_color)
		return(error_map_return((void **)num_color, -1));
	if (array_len(num_color) > 2 || check_digit(num_color[0]))
		return(error_map_return((void **)num_color, 1));
	map->matrix[y][x].x = x;
	map->matrix[y][x].y = y;
	map->matrix[y][x].z = ft_atoi(num_color[0]);
	if (num_color[1])
	{
		map->matrix[y][x].color = get_color(num_color[1], 0);
		if (map->matrix[y][x].color == -1)
			return(error_map_return((void **)num_color, 1));
	}
	else
		map->matrix[y][x].color = 0XFFFFFF;
	free_array((void **)num_color);
	return (0);
}
