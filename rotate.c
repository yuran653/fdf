/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:20:04 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/21 22:28:12 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_rotate_value(int keycode, t_fdf *map)
{
	if (keycode == 0)
		map->rotate->alpha -= 0.025;//0.025;
	else if (keycode == 2)
		map->rotate->alpha += 0.025;//0.025;
	printf("ALPHA = %f | COS(ALPHA) = %f | SIN(ALPHA) = %f\n",
		map->rotate->alpha, cos(map->rotate->alpha), sin(map->rotate->alpha));
}

void	set_projection(int keycode, t_fdf *map)
{
	if (keycode == 34)
	{
		if (map->projection != ISO)
			map->angle_default = 0.175;
		map->projection = ISO;
	}
	else if (keycode == 35)
	{
		if (map->projection != PARALLEL)
			map->angle_default = 0;
		map->projection = PARALLEL;
	}
	map->angle = M_PI * map->angle_default;
}

void	rotate_simple(int keycode, t_fdf *map)
{
	
	if (keycode == 12)
	{
		if (map->angle_default > 0.025)
			map->angle_default -= 0.025;
		else
			map->angle_default = 2;
	}
	else if (keycode == 14)
	{
		if (map->angle_default < 2)
			map->angle_default += 0.025;
		else
			map->angle_default = 0.025;
	}
	map->angle = M_PI * map->angle_default;
}

// e -> 14
// q -> 12
// a -> 0
// d -> 2
