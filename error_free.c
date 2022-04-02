/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:41:23 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/02 07:33:37 by jgoldste         ###   ########.fr       */
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

void	error_free_array_exit(t_fdf *map, char **array)
{
	free_map(map);
	free_char_array(array);
	error_common();
}

void	error_free_all_exit(t_fdf *map, char **array1, char **array2, int is_map)
{
	free_map(map);
	free_char_array_2(array1, array2);
	if (is_map)
		error_map();
	else
		error_common();
}
