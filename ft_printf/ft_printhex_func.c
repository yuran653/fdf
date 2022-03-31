/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:58:31 by jgoldste          #+#    #+#             */
/*   Updated: 2021/11/18 06:58:34 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_hex(t_arg a_val, t_flag *p_str, const char **sp, int *c)
{
	if ((*p_str).align == 1)
	{
		if ((*p_str).precision == 1)
			(*p_str).zero = 0;
		if ((*p_str).hash == 1)
			(*p_str).nbr_sign = 2;
		(*p_str).tmp_width = (*p_str).prec_width;
		(*p_str).nbr_len = ft_hexlen_pf(ft_longlong(a_val, sp));
		if ((*p_str).prec_width < (*p_str).nbr_len)
			(*p_str).prec_width = 0;
		ft_print_a_hex(ft_longlong(a_val, sp), p_str, sp, c);
	}
	else
	{
		(*p_str).tmp_width = (*p_str).prec_width;
		if ((*p_str).precision == 1)
			(*p_str).zero = 0;
		if ((*p_str).hash == 1)
			(*p_str).nbr_sign = 2;
		(*p_str).nbr_len = ft_hexlen_pf(ft_longlong(a_val, sp));
		(*p_str).prec_width -= (*p_str).nbr_len;
		if ((*p_str).prec_width < 0)
			(*p_str).prec_width = 0;
		ft_print_hex(ft_longlong(a_val, sp), p_str, sp, c);
	}
}

void	ft_puthex_x(t_flag *p_str, const char **sp)
{
	if ((*p_str).hash == 1)
	{
		if (**sp == 'x')
			(*p_str).tmp += write(1, "0x", 2);
		if (**sp == 'X')
			(*p_str).tmp += write(1, "0X", 2);
	}
}

void	ft_print_a_hex(long long hex, t_flag *p_str, const char **sp, int *c)
{
	if ((*p_str).hash == 1)
		ft_puthex_x(p_str, sp);
	if ((*p_str).precision == 1)
		(*p_str).prec_width -= (*p_str).nbr_len;
	if ((*p_str).zero == 1)
		while ((*p_str).width-- > 0)
			(*p_str).tmp += write(1, "0", 1);
	while ((*p_str).prec_width-- > 0)
		(*p_str).tmp += write(1, "0", 1);
	*c += (*p_str).tmp;
	if ((*p_str).precision == 1 && (*p_str).tmp_width == 0)
		ft_putzero_hex(hex, p_str, sp, c);
	else
		ft_putnbrhex_pf(hex, sp, c);
	(*p_str).width -= ((*p_str).tmp + (*p_str).nbr_len);
	while ((*p_str).width-- > 0)
		*c += write(1, " ", 1);
}

void	ft_print_hex(long long hex, t_flag *p_str, const char **sp, int *c)
{
	(*p_str).amount = ((*p_str).nbr_sign
			+ (*p_str).prec_width + (*p_str).nbr_len);
	(*p_str).width -= (*p_str).amount;
	if ((*p_str).zero == 0)
	{
		if ((*p_str).precision == 1 && (*p_str).tmp_width == 0
			&& (*p_str).width >= 0 && hex == 0)
			while ((*p_str).width-- >= 0)
				*c += write(1, " ", 1);
		else if ((*p_str).precision == 1 && (*p_str).tmp_width == 0)
			ft_putzero_hex(hex, p_str, sp, c);
		else
		{
			while ((*p_str).width-- > 0)
				(*p_str).tmp += write(1, " ", 1);
			if (hex != 0)
				ft_puthex_x(p_str, sp);
			while ((*p_str).prec_width-- > 0)
				(*p_str).tmp += write(1, "0", 1);
			ft_putnbrhex_pf(hex, sp, c);
			*c += (*p_str).tmp;
		}
	}
	else
		ft_print_z_hex(hex, p_str, sp, c);
}

void	ft_print_z_hex(long long hex, t_flag *p_str, const char **sp, int *c)
{
	while ((*p_str).width-- > 0)
	{
		if ((*p_str).zero == 1)
			*c += write(1, "0", 1);
		else
			*c += write(1, " ", 1);
	}
	ft_puthex_x(p_str, sp);
	if ((*p_str).precision == 1 && (*p_str).tmp_width == 0)
		ft_putzero_hex(hex, p_str, sp, c);
	else
	{
		while ((*p_str).prec_width-- > 0)
			*c += write(1, "0", 1);
		ft_putnbrhex_pf(hex, sp, c);
	}
}
