/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:54 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/01 00:21:33 by jgoldste         ###   ########.fr       */
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
void	error_common(void);
void	error_malloc(void);
void	error_file(char *file_name, int fd);
void	error_file_dir(char *file_name, int fd);
void	error_malloc_free_fdf(t_fdf *map);
void	error_close_free(t_fdf *map, char *str);

#endif