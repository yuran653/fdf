/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:09:03 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/23 16:59:52 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static void	print_how_to_use_continue(t_fdf *map, int y)
// {
	
// }

void	print_how_to_use(t_fdf *map, int y)
{
	mlx_string_put(map->mlx_ptr, map->win_ptr, 10, y += 10, 0XFFFFFF,
		"HOW TO USE:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, y += 40, 0XFFFFFF,
		"To move image:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use arrows UP, DOWN, LEFT, RIGHT");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, y += 40, 0XFFFFFF,
		"To rotate image:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 40, y += 20, 0XFFFFFF,
		"over ABSCISSA axis:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'D' to rotate clock-wise");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'A' to rotate counterclock-wise");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 40, y += 20, 0XFFFFFF,
		"over ORDINATE axis:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'S' to rotate clock-wise");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'W' to rotate counterclock-wise");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 40, y += 20, 0XFFFFFF,
		"over ALTITUDE axis:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'E' to rotate clock-wise");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'Q' to rotate counterclock-wise");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, y += 40, 0XFFFFFF,
		"To stretch / compress image:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'Page UP' to stretch");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'Page DOWN' to compress");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, y += 40, 0XFFFFFF,
		"To zoom image:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use '+' to increase zoom");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use '-' to decrease zoom");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, y += 40, 0XFFFFFF,
		"To change projection type:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'P' to set PARALLEL progection");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'I' to set ISOMETRIC projection");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, y += 40, 0XFFFFFF,
		"To change color:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'C' to set RGB color");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'X' to reset color to default");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, y += 40, 0XFFFFFF,
		"Reset to default:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'H' to reset image to default");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, y += 40, 0XFFFFFF,
		"Exit:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, 0XFFFFFF,
		"use 'ESC' to exit");
}

void	set_projection(int keycode, t_fdf *map)
{
	if (keycode == PROJ_ISOMETRIC)
	{
		if (map->projection != ISO)
		{
			map->rotate->alpha = map->rotate_save->alpha;
			map->rotate_save->alpha = 0;
			map->rotate->beta = map->rotate_save->beta;
			map->rotate_save->beta = 0;
			map->angle_rt = 0.175;
		}
		map->projection = ISO;
	}
	else if (keycode == PROJ_PARALLEL)
	{
		if (map->projection != PARALLEL)
		{
			map->rotate_save->alpha = map->rotate->alpha;
			map->rotate->alpha = 0;
			map->rotate_save->beta = map->rotate->beta;
			map->rotate->beta = 0;
			map->angle_rt = 0;
		}
		map->projection = PARALLEL;
	}
	map->angle = M_PI * map->angle_rt;
}