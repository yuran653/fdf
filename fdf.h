/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:54 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/02 17:34:56 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "./libft/libft.h"
#include "./ft_printf/ft_printf.h"
#include "./get_next_line/get_next_line.h"
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct s_fdf
{
	int	x;
	int	y;
	int	**z;
}	t_fdf;

t_fdf	*validation(char *argv);
void	valid_file_name(char *argv);
void	free_array(void **array);
void	free_array_2(void **array1, void **array2);
void	free_map(t_fdf *map);
void	error_common(void);
void	error_map(void);
void	error_file(char *file_name, int fd);
void	error_free_exit(void *value);
void	error_free_exit_2(void *value1, void *value2);
void	error_free_map_exit(t_fdf *map);
void	error_free_array_exit(t_fdf *map, void **array);
void	error_free_all_exit(t_fdf *map, void **array1, void **array2, int is_map);

void	check_leak();

#endif