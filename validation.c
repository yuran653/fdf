/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:06:59 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/02 19:47:41 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_z(t_fdf *map, char **map_split, char **str_split, int i)
{
	int	*array;
	int	j;

	j = -1;
	array = (int *)malloc(sizeof(int) * map->x);
	if (!array)
		error_free_all_exit(map, (void **)map_split, (void **)str_split, 0);
	while (++j < map->x)
		array[j] = ft_atoi(str_split[j]);
	map->z[i] = array;
}

void	set_check_x(t_fdf *map, char **map_split, char **str_split, int i)
{
	int	j;

	j = 0;
	while (str_split[j])
		j++;
	if (i == 0)
		map->x = j;
	else if (map->x != j)
		error_free_all_exit(map, (void **)map_split, (void **)str_split, 1);
	get_z(map, map_split, str_split, i);
}

void	get_x(t_fdf *map, char *map_str)
{
	int		i;
	char	**map_split;
	char	**str_split;

	i = 0;
	map_split = ft_split(map_str, '\n');
	free(map_str);
	if (!map_split)
		error_free_map_exit(map);
	while (map_split[i])
	{
		str_split = ft_split(map_split[i++], ' ');
		if (!str_split)
			error_free_array_exit(map, (void **)map_split);
		set_check_x(map, map_split, str_split, i - 1);
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
	int		i;

	i = 0;
	valid_file_name(argv);
	fd = open(argv, O_RDONLY);
	error_file(argv, fd);
	map = (t_fdf *)malloc(sizeof(t_fdf));
	if (!map)
		error_common();
	map->z = NULL;
	map_str = get_y(map, fd);
	if (!map_str)
		error_free_exit(map);
	if (close(fd) == -1)
		error_free_exit_2(map, map_str);
	map->z = (int **)malloc(sizeof(int *) * (map->y + 1));
	if (!map->z)
		error_free_array_exit(map, (void **)map_str);
	while (i <= map->y)
		map->z[i++] = NULL;
	get_x(map, map_str);
	return (map);
}
