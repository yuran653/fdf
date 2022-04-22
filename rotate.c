/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:20:04 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/22 21:05:29 by jgoldste         ###   ########.fr       */
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

