/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:06:59 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/10 22:45:04 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_zx_zy(t_fdf *map)
{
	t_point *fix;
	t_point	*zy;

	fix = map->head;
	zy = map->head;
	while (!zy->y)
		zy = zy->next;
	while(map->head)
	{
		if (map->head->next)
			if (map->head->y == map->head->next->y)
				map->head->zy = map->head->next->z;
		map->head = map->head->next;
	}
	map->head = fix;
}

void	get_values(t_fdf *map, char **map_split, char **str_split, int height)
{
	int	err;
	int	width;

	width = 0;
	while (str_split[width])
		width++;
	if (height == 0)
		map->width = width;
	else if (map->width != width)
		error_free_all_exit(map, (void **)map_split, (void **)str_split, 1);
	width = 0;
	while (width < map->width)
	{
		err = fill_values(map, str_split, width++, height);
		if (err == 1)
			error_free_all_exit(map, (void **)map_split, (void **)str_split, 1);
		if (err == -1)
			error_free_all_exit(map, (void **)map_split, (void **)str_split, 0);
	}
}

void	get_width(t_fdf *map, char *map_str)
{
	int		height;
	char	**map_split;
	char	**str_split;

	height = 0;
	map_split = ft_split(map_str, '\n');
	free(map_str);
	if (!map_split)
		error_free_map_exit(map);
	while (map_split[height])
	{
		str_split = ft_split(map_split[height++], ' ');
		if (!str_split)
			error_free_array_exit(map, (void **)map_split);
		get_values(map, map_split, str_split, height - 1);
		free_array((void **)str_split);
	}	
	free_array((void **)map_split);
}

char	*get_height(t_fdf *map, int fd)
{
	char	*map_str;
	char	*line;

	map->height = 0;
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
			map->height++;
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
	map->head = NULL;
	map->end = NULL;
	map->data = NULL;
	map_str = get_height(map, fd);
	if (!map_str)
		error_free_exit(map);
	if (close(fd) == -1)
		error_free_str_exit(map, map_str);
	get_width(map, map_str);
	set_zx_zy(map);
	return (map);
}
