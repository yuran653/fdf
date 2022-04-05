/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:01:32 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/05 03:57:47 by jgoldste         ###   ########.fr       */
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
	while(base[i])
	{
		if (hex == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	get_color(char *hex)
{
	int	hex_num;
	int	hex_read;
	
	hex_num = 0;
	hex_read = 0;
	if (*hex == '0')
		hex++;
	else
		return (-1);
	if (ft_toupper(*hex) == 'X')
		hex++;
	else
		return (-1);
	while (*hex)
	{
		hex_read = check_hex(ft_toupper(*hex), "0123456789ABCDEF");
		if (hex_read >= 0)
			hex_num = hex_num * 16 + hex_read;
		else
			return (-1);
		hex++;
	}
	return (hex_num);
}

int	set_z_color(t_fdf *map, char **str_split, int x, int y)
{
	char	**num_color;
	
	num_color = ft_split(str_split[x], ',');
	if (!num_color)
	{
		free_array((void **)num_color);
		return (-1);
	}
	if (array_len(num_color) > 2 || check_digit(num_color[0]))
	{	
		free_array((void **)num_color);
		return (1);
	}
	map->z[y][x] = ft_atoi(num_color[0]);
	if (!num_color[1])
		map->color[y][x] = 0;
	else
	{
		map->color[y][x] = get_color(num_color[1]);
		if (map->color[y][x] == -1)
			return (-1);
	}
	free_array((void **)num_color);
	return (0);
}