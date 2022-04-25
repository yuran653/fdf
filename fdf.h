/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:54 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/25 16:44:30 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define _USE_MATH_DEFINES
# define BASE16 "0123456789ABCDEF"

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "./get_next_line/get_next_line.h"
# include "keys_define.h"
# include <mlx.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define R_MASK		0xFF0000
# define R_SHIFT	16
# define G_MASK		0x00FF00
# define G_SHIFT	8
# define B_MASK		0x0000FF
# define B_SHIFT	0
# define COLOR_MAIN 0XDADADA

# define SCR_WIDTH	1920
# define SCR_HEIGHT 1280

typedef enum s_project
{
	ISO,
	PARALLEL	
}	t_project;

typedef enum s_color
{
	DEFAULT,
	RGB
}	t_color;

typedef enum s_direct
{
	CLOCKWISE,
	CNTRCLOCK
}	t_direct;

typedef struct s_steps
{
	double	x_step;
	double	y_step;
	int		max;
	int		i;
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

typedef struct s_rotate
{
	double	alpha;
	double	alpha_rt;
	double	beta;
	double	beta_rt;
	double	gamma;
	double	gamma_rt;
}	t_rotate;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_fdf
{
	t_point		**matrix;
	t_point		tmp;
	t_project	projection;
	t_color		color;
	int			width;
	int			height;
	int			x_shift;
	int			y_shift;
	double		z_shift;
	double		z_zoom;
	double		zoom;
	double		z_min;
	double		z_max;
	double		angle;
	double		angle_rt;
	void		*mlx_ptr;
	void		*win_ptr;
	t_data		*data;
	t_rotate	*rotate;
	t_rotate	*rotate_save;
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
int		key_hook(int keycode, t_fdf *map);
void	set_default(t_fdf *map);
void	set_projection(int keycode, t_fdf *map);
void	set_color(t_point *point, t_fdf *map);
int		get_gradient(int start, int end, int len, int i);
void	make_rotate(int keycode, t_fdf *map);
void	rotate_abscissa(t_point *point, t_fdf *map);
void	rotate_ordinate(t_point *point, t_fdf *map);
void	rotate_altitude(t_point *point, t_fdf *map);
void	print_how_to_use(t_fdf *map, int y);
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
int		close_win_exit(t_fdf *map);

#endif
