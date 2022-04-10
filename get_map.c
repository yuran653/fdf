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

void	append_point(t_fdf *map, t_point *point)
{
	if (!map->end)
	{
		map->head = point;
		map->end = point;
		ft_printf("HEAD POINT APPENDED: x = %d y = %d z = %d color = %X\n\n",
			map->end->x, map->end->y,map->end->z, map->end->color);
	}
	else
	{
		ft_printf("before map->end->next value = %p\n", map->end->next);
		map->end->next = point;
		ft_printf(" after map->end->next value = %p\n", map->end->next);
		ft_printf("     POINT APPENDED: x = %d y = %d z = %d color = %X\n\n",
			map->end->x, map->end->y,map->end->z, map->end->color);
	}
}

t_point	*init_pixel(int x, int y, int z, int color)
{
	t_point *point;

	point = (t_point *) malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = color;
	point->next = NULL;
	return (point);
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
	int z = ft_atoi(num_color[0]);
	ft_printf("POINT TO INITIALIZE: x = %d y = %d z = %d color = %X\n", x, y, z, color);
	// point = init_pixel(x, y, ft_atoi(num_color[0]), color);
	point = init_pixel(x, y, z, color);
	if (!point)
		return(error_map_return((void **)num_color, -1));
	ft_printf("  POINT TO APPENDED: x = %d y = %d z = %d color = %X\n",
		point->x, point->y, point->z, point->color);
	append_point(map, point);
	free_array((void **)num_color);
	return (0);
}
