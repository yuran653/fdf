/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:06:59 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/05 00:14:11 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_z(t_fdf *map, char **map_split, char **str_split, int y)
{
	int	err;
	int	x;
	
	x = 0;
	while (str_split[x])
		x++;
	if (y == 0)
		map->x = x;
	else if (map->x != x)
		error_free_all_exit(map, (void **)map_split, (void **)str_split, 1);
	map->z[y] = (int *)malloc(sizeof(int) * map->x);
	if (!map->z[y])
		error_free_all_exit(map, (void **)map_split, (void **)str_split, 0);
	map->color[y] = (int *)malloc(sizeof(int) * map->x);
	if (!map->color[y])
		error_free_all_exit(map, (void **)map_split, (void **)str_split, 0);
	x = 0;
	while (x < map->x)
	{
		err = get_color(map, str_split, x++, y);
		if (err == 1)
			error_free_all_exit(map, (void **)map_split, (void **)str_split, 1);
		if (err == -1)
			error_free_all_exit(map, (void **)map_split, (void **)str_split, 0);
	}
}

void	get_x(t_fdf *map, char *map_str)
{
	int		y;
	char	**map_split;
	char	**str_split;

	y = 0;
	map_split = ft_split(map_str, '\n');
	free(map_str);
	if (!map_split)
		error_free_map_exit(map);
	while (map_split[y])
	{
		str_split = ft_split(map_split[y++], ' ');
		if (!str_split)
			error_free_array_exit(map, (void **)map_split);
		get_z(map, map_split, str_split, y - 1);
		free_array((void **)str_split);
	}	
	free_array((void **)map_split);
}

char	*get_y(t_fdf *map, int fd)
{
	char	*map_str;
	char	*line;

	map->y = 0;
	map_str = (char *)malloc(sizeof(char));
	if (!map_str)
		error_free_exit(map);
	map_str[0] = '\0';
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (map_str);
		if (line[0] != '\n')
		{
			map->y++;
			map_str = ft_strjoin_gnl(map_str, line);
			if (!map_str)
				error_free_str_exit(map, line);
		}
		free(line);
	}
	return (NULL);
}

t_fdf	*validation(char *argv)
{
	t_fdf	*map;
	char	*map_str;
	int		fd;

	valid_file_name(argv);
	fd = open(argv, O_RDONLY);
	error_file(argv, fd);
	map = (t_fdf *)malloc(sizeof(t_fdf));
	if (!map)
		error_common();
	map->z = NULL;
	map->color = NULL;
	map_str = get_y(map, fd);
	if (!map_str)
		error_free_exit(map);
	if (close(fd) == -1)
		error_free_str_exit(map, map_str);
	calloc_arrays(map, map_str);
	get_x(map, map_str);
	return (map);
}
