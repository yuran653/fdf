/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:06:59 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/02 04:28:20 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
}

// void	set_z()

void	get_x_z(t_fdf *map, char *map_str)
{
	int		i;
	int		*z;
	char	**map_split;
	char	**str_split;

	i = 0;
	map_split = ft_split(map_str, '\n');
	free(map_str);
	if (!map_split)
		error_free_exit_1(map);
	while (map_split[i])
	{
		str_split = ft_split(map_split[i++], ' ');
		if (!str_split)
			error_free_array_exit_2(map, (void **)map_split);
		set_check_x(map, map_split, str_split, i - 1);
		
		// set_z(map, )
		int j;
		for (j = 0; str_split[j]; j++)
			ft_printf("[%3s]", str_split[j]);
		ft_printf("\n");
		free(map);
		free_array_2((void **)map_split, (void **)str_split);
		exit (0);
	}	
	free(map);
	exit(0);
}

char	*get_y(t_fdf *map, int fd)
{
	char	*map_str;
	char	*line;

	map->y = 0;
	map_str = (char *)malloc(sizeof(char));
	if (!map_str)
		error_free_exit_1(map);
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

t_fdf	*validation(char *argv)
{
	t_fdf 	*map;
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
	map_str = get_y(map, fd);
	if (!map_str)
		error_free_exit_1(map);
	if (close(fd) == -1)
		error_free_array_exit_2(map, (void **)map_str);
	map->z = (int **)malloc(sizeof(int *) * (map->y + 1));
	if (!map->z)
		error_free_array_exit_2(map, (void **)map_str);
	while (i <= map->y)
		map->z[i++] = NULL;
	get_x_z(map, map_str);
	// map->z = get_z(argv);
	free(map_str);
	return (map);
}