/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:06:59 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/01 01:07:25 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_map()
{
	ft_printf("WTF\n");
	exit(0);
}

char	**get_x(t_fdf *map, char *map_str)
{
	int		i;
	char	**map_split;

	i = -1;
	map_split = ft_split(map_str, '\n');
	free(map_str);
	map->x = ft_strlen(map_split[0]);
	while (map_split[++i])
	{
		if (ft_strlen(map_split[i]) != (unsigned long)map->x)
			error_map();//(map, map_split);
	}	
	free(map);
	exit(0);
	return (map_split);
}

char	*get_y(t_fdf *map, int fd)
{
	char	*map_str;
	char	*line;

	map->y = 0;
	map_str = (char *)malloc(sizeof(char));
	if (!map_str)
		error_malloc_free_fdf(map);
	map_str[0] = '\0';
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (map_str);
		map->y++;
		map_str = ft_strjoin_gnl(map_str, line);
		free(line);
	}
	return (NULL);
}

// int	**get_z(char **map_str)
// {

// }

t_fdf	*validation(char *argv)
{
	t_fdf 	*map;
	char	*map_str;
	char	**map_split;
	int		fd;
	
	fd = open(argv, O_RDONLY);
	error_file(argv, fd);
	map = (t_fdf *)malloc(sizeof(t_fdf));
	if (!map)
		error_malloc();
	map_str = get_y(map, fd);
	if (!map_str)
		error_malloc_free_fdf(map);
	if (close(fd) == -1)
		error_close_free(map, map_str);
	map_split = get_x(map, map_str);
	// map->z = get_z(argv);
	free(map_str);
	return (map);
}