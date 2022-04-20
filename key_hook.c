/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:37:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/20 19:12:08 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translate(int keycode, t_fdf *map)
{
	if (keycode == 123 && map->x_shift > -(SCR_WIDTH + SCR_WIDTH / 2))
		map->x_shift -= 5;
	else if (keycode == 124 && map->x_shift < (SCR_WIDTH + SCR_WIDTH / 2))
		map->x_shift += 5;
	else if (keycode == 125 && map->y_shift < (SCR_HEIGHT + SCR_HEIGHT / 2))
		map->y_shift += 5;
	else if (keycode == 126 && map->y_shift > -(SCR_HEIGHT + SCR_HEIGHT / 2))
		map->y_shift -= 5;
}

static void	color_zoom(int keycode, t_fdf *map)
{
	if (keycode == 7)
		map->clr_opt = 1;
	else if (keycode == 8)
		map->clr_opt = 3;
	else if (keycode == 69 && map->zoom < 2000)
		map->zoom *= 1.029999999999999;
	else if (keycode == 78 && map->zoom > 1.03 && map->zoom < 2000)
		map->zoom /= 1.029999999999999;
}

static void	stretch_compress(int keycode, t_fdf *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (keycode == 116)
			{
				if (ft_abs(map->matrix[y][x].z) > 1)
					map->matrix[y][x].z *= 1.049999999999999;
				else
					map->matrix[y][x].z *= 1.149999999999999;
			}
			if (keycode == 121)
			{
				if (ft_abs(map->matrix[y][x].z) > 1)
					map->matrix[y][x].z /= 1.049999999999999;
				else
					map->matrix[y][x].z /= 1.149999999999999;
			}
		}
	}
}

static	void	set_new_image(t_fdf *map)
{
	mlx_destroy_image(map->mlx_ptr, map->data->img);
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	map->data->img = mlx_new_image(map->mlx_ptr, SCR_WIDTH, SCR_HEIGHT);
	map->data->addr = mlx_get_data_addr(map->data->img,
			&map->data->bits_per_pixel, &map->data->line_length,
			&map->data->endian);
	draw_map(map);
}

int	key_hook(int keycode, t_fdf *map)
{
	if (keycode == 53)
		error_free_map_win_exit(map, EXIT_SUCCESS);
	else if (keycode == 4)
		set_default(map);
	else if (keycode == 7 || keycode == 8 || keycode == 69 || keycode == 78)
		color_zoom(keycode, map);
	else if (keycode >= 123 && keycode <= 126)
		translate(keycode, map);
	else if (keycode == 116 || keycode == 121)
		stretch_compress(keycode, map);
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