/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:34:32 by jgoldste          #+#    #+#             */
/*   Updated: 2022/03/31 17:32:35 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "../libft/libft.h"

# define FLAGS_DIGITS "-0.# +123456789"
# define SPECIFIERS "cspdiuxX%"

typedef struct s_flag
{
	int	align;
	int	zero;
	int	precision;
	int	hash;
	int	space;
	int	sign;
	int	width;
	int	prec_width;
	int	nbr_len;
	int	nbr_sign;
	int	amount;
	int	tmp;
	int	tmp_width;
}	t_flag;

typedef union s_arg
{
	char				c;
	char				*s;
	int					d;
	unsigned int		u;
	unsigned long long	p;
}	t_arg;

int			ft_printf(const char *str, ...);
void		ft_print_flags(t_arg a_val, t_flag *p_str, const char **sp, int *c);
void		ft_put_zero_pf(t_flag *p_str);
void		ft_putchr_pf(char s, int *c);
void		ft_putstr_pf(char *str, int width, int *c);
int			ft_strchr_pf(char *s, int c);
int			ft_isdigit_pf(int str);
int			ft_nbrlen_pf(long long nbr);
void		ft_putnbrhex_pf(long long num, const char **type, int *c);
void		ft_recurs_hex(unsigned long long num, const char **type, int *c);
void		ft_recurs_nbr(long long num, int *c);
void		ft_getarg(va_list args, t_arg *a_val, const char **sp);
void		ft_parse_flags(t_flag *p_str, const char **flags);
void		ft_parse_value(t_flag *p_str, const char **flags);
void		ft_print_str(t_arg a_val, t_flag *p_str, int *c);
void		ft_print_ptr(t_arg a_val, t_flag *p_str, const char **sp, int *c);
void		ft_print_chr(t_arg a_val, t_flag *p_str, int *c);
void		ft_parse_nbr(t_arg a_val, t_flag *p_str, const char **sp, int *c);
void		ft_print_nbr(t_arg a_val, t_flag *p_str, const char **sp, int *c);
void		ft_print_a_nbr(t_arg a_val, t_flag *p_str, const char **sp, int *c);
void		ft_print_p_nbr(t_arg a_val, t_flag *p_str, const char **sp, int *c);
void		ft_print_z_nbr(t_arg a_val, t_flag *p_str, const char **sp, int *c);
int			ft_print_sign(t_flag *p_str, long long num, int *c);
long long	ft_longlong(t_arg a_val, const char **sp);
void		ft_parse_hex(t_arg a_val, t_flag *p_str, const char **sp, int *c);
int			ft_hexlen_pf(unsigned long long hex);
void		ft_print_per(t_arg a_val, t_flag *p_str, int *c);
void		ft_puthex_x(t_flag *p_str, const char **sp);
void		ft_print_hex(long long hex, t_flag *p_str, const char **sp, int *c);
void		ft_print_a_hex(long long hex, t_flag *p_str,
				const char **sp, int *c);
void		ft_print_z_hex(long long hex, t_flag *p_str,
				const char **sp, int *c);
void		ft_putzero_hex(long long hex, t_flag *p_str,
				const char **sp, int *c);

#endif
