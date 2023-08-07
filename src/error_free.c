/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:41:23 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/04 19:38:11 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_free_exit(void *value)
{
	free(value);
	error_common();
}

void	error_free_map_exit(t_fdf *map)
{
	free_map(map);
	error_common();
}

void	error_free_str_exit(t_fdf *map, char *str)
{
	free(str);
	error_free_map_exit(map);
}

void	error_free_array_exit(t_fdf *map, void **array)
{
	free_map(map);
	free_array(array);
	error_common();
}

void	error_free_all_exit(t_fdf *map, void **arr1, void **arr2, int is_map)
{
	free_map(map);
	free_array_2((void **)arr1, (void **)arr2);
	if (is_map)
		error_map();
	else
		error_common();
}
