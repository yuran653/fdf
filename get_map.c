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

void	append_point(t_fdf *map, t_point *point)
{
	if (!map->end)
		map->head = point;
	else
		map->end->next = point;
	map->end = point;
}

t_point	*init_point(int x, int y, int z, int color)
{
	t_point *point;

	point = (t_point *) malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	point->zx = 0;
	point->zy = 0;
	point->color = color;
	point->next = NULL;
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
	t_point	*point;

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
	point = init_point(x, y, ft_atoi(num_color[0]), color);
	if (!point)
		return(error_map_return((void **)num_color, -1));
	append_point(map, point);
	free_array((void **)num_color);
	return (0);
}
