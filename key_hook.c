/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:37:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/20 13:12:28 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	set_new_z_value(t_fdf *map, int diff)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y < map->height)
// 	{
// 		x = -1;
// 		while (++x < map->width)
// 		{
// 			if (map->matrix[y][x].z > 0)
// 				map->matrix[y][x].z += diff;
// 			if (map->matrix[y][x].z < 0)
// 				map->matrix[y][x].z -= diff;
// 			if (!map->matrix[y][x].z)
// 			{
// 				if (map->matrix[y][x].z_default > 0 && diff > 0)
// 					map->matrix[y][x].z += diff;
// 				if (map->matrix[y][x].z_default < 0 && diff < 0)
// 					map->matrix[y][x].z += diff;
// 			}
// 		}
// 	}
// }

void	set_new_z_value(t_fdf *map, int diff)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (diff == 1)
				map->matrix[y][x].z *= 1.049999;
			if (diff == -1)
				map->matrix[y][x].z /= 1.049999;
			// if (map->matrix[y][x].z > 0)
			// 	map->matrix[y][x].z += diff;
			// if (map->matrix[y][x].z < 0)
			// 	map->matrix[y][x].z -= diff;
			// if (!map->matrix[y][x].z)
			// {
			// 	if (map->matrix[y][x].z_default > 0 && diff > 0)
			// 		map->matrix[y][x].z += diff;
			// 	if (map->matrix[y][x].z_default < 0 && diff < 0)
			// 		map->matrix[y][x].z += diff;
			// }
		}
	}
}

void	set_new_image(t_fdf *map)
{
	mlx_destroy_image(map->mlx_ptr, map->data->img);
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	map->data->img = mlx_new_image(map->mlx_ptr, SCR_WIDTH, SCR_HEIGHT);
	map->data->addr = mlx_get_data_addr(map->data->img,
		&map->data->bits_per_pixel, &map->data->line_length, &map->data->endian);
	draw_map(map);
}

int	key_hook(int keycode, t_fdf *map)
{
	if (keycode == 53)
		error_free_map_win_exit(map, EXIT_SUCCESS);
	else if (keycode == 4)
		set_default(map);
	else if (keycode == 69)
		map->zoom += 1;
	else if (keycode == 78)
		map->zoom -= 1;
	else if (keycode == 124)
		map->x_shift += 5;
	else if (keycode == 123)
		map->x_shift -= 5;
	else if (keycode == 126)
		map->y_shift -= 5;
	else if (keycode == 125)
		map->y_shift += 5;
	else if (keycode == 116)
		set_new_z_value(map, 1);
	else if (keycode == 121)
		set_new_z_value(map, -1);
		else if (keycode == 7)
		map->clr_opt = 1;
	else if (keycode == 8)
		map->clr_opt = 3;
	else
	{
		ft_printf("keycode = [%d]\n", keycode);
		return (0);
	}
	set_new_image(map);
	return (0);
}

// h -> 4
// + -> 69
// - -> 78
// right -> 124
// left -> 123
// up -> 126
// down -> 125
// pgup -> 116
// pgdn -> 121
// c -> 8
// x -> 7