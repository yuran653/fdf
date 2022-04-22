/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:39:55 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/22 20:42:35 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_leak(void)
{
	exit(EXIT_SUCCESS);
}

void	free_array(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
}

void	free_array_2(void **array1, void **array2)
{
	free_array(array1);
	free_array(array2);
}

void	free_map(t_fdf *map)
{
	if (map->matrix)
		free_array((void **)map->matrix);
	if (map->data)
		free(map->data);
	map->data = NULL;
	if (map->rotate)
		free(map->rotate);
	map->rotate = NULL;
	if (map->rotate_save)
		free(map->rotate_save);
	map->rotate_save = NULL;
	free(map);
	map = NULL;
}

void	error_free_map_win_exit(t_fdf *map, int err)
{
	mlx_destroy_image(map->mlx_ptr, map->data->img);
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	free_map(map);
	if (!err)
		exit(EXIT_SUCCESS);
	error_common();
}
