/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:37:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/22 15:47:09 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translate(int keycode, t_fdf *map)
{
	if (keycode == ARROW_LEFT
		&& map->x_shift > -(SCR_WIDTH + SCR_WIDTH / 2))
		map->x_shift -= 5;
	else if (keycode == ARROW_RIGHT
		&& map->x_shift < (SCR_WIDTH + SCR_WIDTH / 2))
		map->x_shift += 5;
	else if (keycode == ARROW_DOWN
		&& map->y_shift < (SCR_HEIGHT + SCR_HEIGHT / 2))
		map->y_shift += 5;
	else if (keycode == ARROW_UP
		&& map->y_shift > -(SCR_HEIGHT + SCR_HEIGHT / 2))
		map->y_shift -= 5;
}

static void	color_zoom(int keycode, t_fdf *map)
{
	if (keycode == COLOR_DEFAULT)
		map->color = DEFAULT;
	else if (keycode == COLOR_RGB)
		map->color = RGB;
	else if (keycode == 69 && map->zoom < 2000)
		map->zoom *= 1.029999999999999;
	else if (keycode == 78 && map->zoom > 1.03)
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
	if (keycode == ESCAPE)
		error_free_map_win_exit(map, EXIT_SUCCESS);
	else if (keycode == SET_DEFAULT)
		set_default(map);
	else if (keycode == COLOR_DEFAULT || keycode == COLOR_RGB
		|| keycode == ZOOM_PLUS || keycode == ZOOM_MINUS)
		color_zoom(keycode, map);
	else if (keycode == ARROW_LEFT || keycode == ARROW_RIGHT
		|| keycode == ARROW_DOWN || keycode == ARROW_UP)
		translate(keycode, map);
	else if (keycode == STRETCH || keycode == COMPRESS)
		stretch_compress(keycode, map);
	else if ((keycode == CNTRCLOCK_ALT || keycode == CLOCKWISE_ALT)
		&& map->projection == PARALLEL)
		make_rotate(keycode, map);
	else if ((keycode == CNTRCLOCK_ABS || keycode == CLOCKWISE_ABS)
		&& map->projection == ISO)
		make_rotate(keycode, map);
	else if (keycode == PROJ_ISOMETRIC || keycode == PROJ_PARALLEL)
		set_projection(keycode, map);
	else
	{
		ft_printf("keycode = [%d]\n", keycode);
		return (0);
	}
	set_new_image(map);
	return (0);
}

// esc -> 53
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
// z -> 6
// e -> 14
// q -> 12
// i -> 34
// p -> 35
// a -> 0
// d -> 2
// w -> 13
// s -> 1

// else if (keycode == 6 || keycode == 7 || keycode == 8
// 		|| keycode == 69 || keycode == 78)

	// else if ((keycode == CNTRCLOCKWISE_ALT || keycode == CLOCKWISE_ALT)
	// 	&& map->projection == PARALLEL)
	// 	rotate_simple(keycode, map);
	// else if ((keycode == CNTRCLOCKWISE_ALT || keycode == CLOCKWISE_ALT)
	// 	&& map->projection == ISO)
	// 	rotate_isometric(keycode, map);