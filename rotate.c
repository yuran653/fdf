/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:20:04 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/22 16:53:04 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_values(t_direct value, double *angle, double *angle_rotate)
{
	if (value == CNTRCLOCK)
	{
		if (*angle_rotate > 0.025)
			*angle_rotate -= 0.025;
		else
			*angle_rotate = 2;
	}
	else if (value == CLOCKWISE)
	{
		if (*angle_rotate < 1.975)
			*angle_rotate += 0.025;
		else
			*angle_rotate = 0.025;
	}
	*angle = M_PI * *angle_rotate;
}

void	make_rotate(int keycode, t_fdf *map)
{
	if (keycode == CLOCKWISE_ABS)
		rotate_values(CLOCKWISE, &map->rotate->alpha, &map->rotate->alpha_rt);
	else if (keycode == CNTRCLOCK_ABS)
		rotate_values(CNTRCLOCK, &map->rotate->alpha, &map->rotate->alpha_rt);
	else if (keycode == CLOCKWISE_ORD)
		rotate_values(CLOCKWISE, &map->rotate->beta, &map->rotate->beta_rt);
	else if (keycode == CNTRCLOCK_ORD)
		rotate_values(CNTRCLOCK, &map->rotate->beta, &map->rotate->beta_rt);
	else if (keycode == CLOCKWISE_ALT && map->projection == ISO)
		rotate_values(CLOCKWISE, &map->rotate->gamma, &map->rotate->gamma_rt);
	else if (keycode == CNTRCLOCK_ALT && map->projection == ISO)
		rotate_values(CNTRCLOCK, &map->rotate->gamma, &map->rotate->gamma_rt);
	else if (keycode == CLOCKWISE_ALT && map->projection == PARALLEL)
		rotate_values(CLOCKWISE, &map->angle, &map->angle_rt);
	else if (keycode == CNTRCLOCK_ALT && map->projection == PARALLEL)
		rotate_values(CNTRCLOCK, &map->angle, &map->angle_rt);
}

void	set_projection(int keycode, t_fdf *map)
{
	if (keycode == 34)
	{
		if (map->projection != ISO)
			map->angle_rt = 0.175;
		map->projection = ISO;
	}
	else if (keycode == 35)
	{
		if (map->projection != PARALLEL)
			map->angle_rt = 0;
		map->projection = PARALLEL;
	}
	map->angle = M_PI * map->angle_rt;
}

// e -> 14
// q -> 12
// a -> 0
// d -> 2

// printf("ALPHA = %f | ROTATE = %f | COS(ALPHA) = %f | SIN(ALPHA) = %f\n",
// 		map->rotate->alpha, map->rotate->alpha_rotate,
// 		cos(map->rotate->alpha), sin(map->rotate->alpha));

// printf("ANGLE = %f | ROTATE = %f | COS(ALPHA) = %f | SIN(ALPHA) = %f\n",
// 		map->angle, map->angle_rotate,
// 		cos(map->angle), sin(map->angle));
