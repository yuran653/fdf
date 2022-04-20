/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:54 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/20 20:38:58 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "./get_next_line/get_next_line.h"
# include <mlx.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# ifndef _USE_MATH_DEFINES
#  define _USE_MATH_DEFINES
# endif

# ifndef BASE16
#  define BASE16 "0123456789ABCDEF"
# endif

# ifndef SCR_WIDTH
#  define SCR_WIDTH 1920
# endif

# ifndef SCR_HEIGHT
#  define SCR_HEIGHT 1280
# endif

typedef struct s_steps
{
	double	x_step;
	double	y_step;
	int		max;
}	t_steps;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	z_default;
	int		color;
	int		color_default;
}	t_point;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_fdf
{
	t_point	**matrix;
	int		width;
	int		height;
	int		clr_opt;
	int		x_shift;
	int		y_shift;
	double	z_shift;
	double	z_zoom;
	double	zoom;
	double	z_min;
	double	z_max;
	double	angle;
	double	rotate_smpl;
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	*data;
}	t_fdf;

t_fdf	*validation(char *argv);
void	valid_file_name(char *argv);
int		fill_values(t_fdf *map, char **str_split, int x, int y);
int		array_len(char **array);
double	ft_min(double a, double b);
double	ft_max(double a, double b);
double	ft_abs(double a);
double	abs_max(double a, double b);
void	draw_map(t_fdf *map);
void	set_default(t_fdf *map);
void	rotate_simple(int keycode, t_fdf *map);
int		key_hook(int keycode, t_fdf *map);
void	check_leak(void);
void	free_array(void **array);
void	free_array_2(void **array1, void **array2);
void	free_map(t_fdf *map);
void	error_free_exit(void *value);
void	error_free_map_exit(t_fdf *map);
void	error_free_str_exit(t_fdf *map, char *str);
void	error_free_array_exit(t_fdf *map, void **array);
void	error_free_all_exit(t_fdf *map, void **arr1, void **arr2, int is_map);
void	error_common(void);
void	error_map(void);
int		error_map_return(void **array, int is_map);
void	error_file(char *file_name, int fd);
void	error_free_map_win_exit(t_fdf *map, int err);

#endif
