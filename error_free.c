/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:41:23 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/02 17:36:10 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_free_exit(void *value)
{
	free(value);
	error_common();
}

void	error_free_exit_2(void *value1, void *value2)
{
	free(value1);
	free(value2);
	error_common();
}

void	error_free_map_exit(t_fdf *map)
{
	free_map(map);
	error_common();
}

void	error_free_array_exit(t_fdf *map, void **array)
{
	free_map(map);
	free_array(array);
	error_common();
}

void	error_free_all_exit(t_fdf *map, void **array1, void **array2, int is_map)
{
	free_map(map);
	free_array_2((void **)array1, (void **)array2);
	if (is_map)
		error_map();
	else
		error_common();
}
