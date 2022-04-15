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

t_point	init_point(int x, int y, int z, int color)
{
	t_point point;

	ft_printf("START INIT_POINT\n");
	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	ft_printf("x = %d, y = %d, z = %d color = %X\n", point.x, point.y, point.z, point.color);
	ft_printf("FINISH INIT_POINT\n");
	return (point);
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

int	fill_values(t_fdf *map, char **str_split, int x, int y)
{
	char	**num_color;
	int		color;

	// if (y == 27)
	// 	ft_printf("\tBEFORE SEGFAULT height = %d width = %d\n", map->height, map->width);
	num_color = ft_split(str_split[x], ',');
	if (!num_color)
		return(error_map_return((void **)num_color, -1));
	if (array_len(num_color) > 2 || check_digit(num_color[0]))
		return(error_map_return((void **)num_color, 1));
	if (num_color[1])
	{
		color = get_color(num_color[1], 0);
		if (color == -1)
			return(error_map_return((void **)num_color, 1));
	}
	else
		color = 0XFFFFFF;
	// map->matrix[y][x] = init_point(x, y, ft_atoi(num_color[0]), color);
	// if (y == 27)
	// 	ft_printf("\t-----OK-----\n");
	free_array((void **)num_color);
	// if (y == 27)
	// 	ft_printf("\tEXIT FILL VALUES\n");
	(void) map;
	(void) x;
	(void) y;
	return (0);
}
