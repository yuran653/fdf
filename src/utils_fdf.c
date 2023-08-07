/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:09:03 by jgoldste          #+#    #+#             */
/*   Updated: 2023/08/07 13:32:26 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_leak(void)
{
	exit(EXIT_SUCCESS);
}

static void	print_how_to_use_other(t_fdf *map, int *y)
{
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, *y += 40, COLOR_MAIN,
		"To stretch / compress image:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'O' to stretch");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'L' to compress");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, *y += 40, COLOR_MAIN,
		"To zoom image:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use '0' to increase zoom");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use '9' to decrease zoom");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, *y += 40, COLOR_MAIN,
		"To change projection type:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'P' to set PARALLEL progection");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'I' to set ISOMETRIC projection");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, *y += 40, COLOR_MAIN,
		"To change color:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'C' to set RGB color");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'X' to reset color to default");
}

static void	print_how_to_use_rotate(t_fdf *map, int *y)
{
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, *y += 40, COLOR_MAIN,
		"To rotate image:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 40, *y += 20, COLOR_MAIN,
		"over ABSCISSA axis:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'D' to rotate clock-wise");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'A' to rotate counterclock-wise");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 40, *y += 20, COLOR_MAIN,
		"over ORDINATE axis:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'S' to rotate clock-wise");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'W' to rotate counterclock-wise");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 40, *y += 20, COLOR_MAIN,
		"over ALTITUDE axis:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'E' to rotate clock-wise");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
		"use 'Q' to rotate counterclock-wise");
}

void	print_how_to_use(t_fdf *map, int y)
{
	mlx_string_put(map->mlx_ptr, map->win_ptr, 10, y += 10, COLOR_MAIN,
		"HOW TO USE:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, y += 40, COLOR_MAIN,
		"To move image:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, COLOR_MAIN,
		"use arrows UP, DOWN, LEFT, RIGHT");
	print_how_to_use_rotate(map, &y);
	print_how_to_use_other(map, &y);
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, y += 40, COLOR_MAIN,
		"Reset to default:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, COLOR_MAIN,
		"use 'H' to reset image to default");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, y += 40, COLOR_MAIN,
		"Exit:");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, y += 20, COLOR_MAIN,
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

// static void	print_how_to_use_other(t_fdf *map, int *y)
// {
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, *y += 40, COLOR_MAIN,
// 		"To stretch / compress image:");
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
// 		"use 'Page UP' to stretch");
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
// 		"use 'Page DOWN' to compress");
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, *y += 40, COLOR_MAIN,
// 		"To zoom image:");
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
// 		"use '+' to increase zoom");
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
// 		"use '-' to decrease zoom");
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, *y += 40, COLOR_MAIN,
// 		"To change projection type:");
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
// 		"use 'P' to set PARALLEL progection");
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
// 		"use 'I' to set ISOMETRIC projection");
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 20, *y += 40, COLOR_MAIN,
// 		"To change color:");
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
// 		"use 'C' to set RGB color");
// 	mlx_string_put(map->mlx_ptr, map->win_ptr, 60, *y += 20, COLOR_MAIN,
// 		"use 'X' to reset color to default");
// }