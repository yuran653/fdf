/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:41:23 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/02 04:20:52 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_free_exit_1(void *value1)
{
	free(value1);
	error_common();
}

void	error_free_array_exit_1(void *array1)
{
	free_array(array1);
	error_common();
}

void	error_free_array_exit_2(void *value, void **array1)
{
	free(value);
	free_array(array1);
	error_common();
}

void	error_free_all_exit(t_fdf *map, void **array1, void **array2, int map)
{
	free_array((void **)map->z);
	free(map);
	free_array_2(array1, array2);
	if (map)
		error_map();
	else
		error_common();
}