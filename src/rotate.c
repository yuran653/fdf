/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:20:04 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/23 19:46:28 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_abscissa(t_point *point, t_fdf *map)
{
	map->tmp.y = point->y * cos(map->rotate->alpha) + point->z
		* sin(map->rotate->alpha);
	point->z = -point->y * sin(map->rotate->alpha) + point->z
		* cos(map->rotate->alpha);
	point->y = map->tmp.y;
}

void	rotate_ordinate(t_point *point, t_fdf *map)
{
	map->tmp.x = point->x * cos(map->rotate->beta) + point->z
		* sin(map->rotate->beta);
	point->z = -point->x * sin(map->rotate->beta) + point->z
		* cos(map->rotate->beta);
	point->x = map->tmp.x;
}

void	rotate_altitude(t_point *point, t_fdf *map)
{
	map->tmp.x = point->x * cos(map->rotate->gamma)
		- point->y * sin(map->rotate->gamma);
	point->y = point->x * sin(map->rotate->gamma)
		+ point->y * cos(map->rotate->gamma);
	point->x = map->tmp.x;
}

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
