/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:55:45 by jgoldste          #+#    #+#             */
/*   Updated: 2021/11/14 13:55:47 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_sign(t_flag *p_str, long long num, int *c)
{
	if (num < 0)
	{
		*c += write(1, "-", 1);
		return (1);
	}
	else if ((*p_str).sign == 1)
	{
		*c += write(1, "+", 1);
		return (1);
	}
	else if ((*p_str).space == 1)
	{
		*c += write(1, " ", 1);
		return (1);
	}
	return (0);
}

void	ft_print_a_nbr(t_arg a_val, t_flag *p_str, const char **sp, int *c)
{
	if ((*p_str).align == 1)
	{
		(*p_str).nbr_sign = ft_print_sign(p_str, ft_longlong(a_val, sp), c);
		if ((*p_str).precision == 1)
		{
			(*p_str).amount = (*p_str).prec_width - (*p_str).nbr_len;
			while ((*p_str).amount-- > 0)
				(*p_str).tmp += write(1, "0", 1);
		}
		*c += (*p_str).tmp;
		if ((*p_str).precision == 1 && (*p_str).prec_width == 0)
		{
			if (ft_longlong(a_val, sp) != 0)
				ft_putnbrhex_pf(ft_longlong(a_val, sp), sp, c);
			else
				(*p_str).nbr_len = 0;
		}
		else
			ft_putnbrhex_pf(ft_longlong(a_val, sp), sp, c);
		(*p_str).nbr_len += (*p_str).nbr_sign;
		(*p_str).tmp += (*p_str).nbr_len;
		(*p_str).amount = (*p_str).width - (*p_str).tmp;
		while ((*p_str).amount-- > 0)
			*c += write(1, " ", 1);
	}
}

void	ft_print_z_nbr(t_arg a_val, t_flag *p_str, const char **sp, int *c)
{
	(*p_str).nbr_len = ft_nbrlen_pf(ft_longlong(a_val, sp));
	if ((*p_str).zero == 1 && ((*p_str).space == 1 || (*p_str).sign == 1
			|| ft_longlong(a_val, sp) < 0))
		ft_print_sign(p_str, ft_longlong(a_val, sp), c);
	if ((*p_str).zero == 1)
	{
		(*p_str).amount = (*p_str).width - (*p_str).nbr_len;
		if (ft_longlong(a_val, sp) < 0)
			((*p_str).amount -= 1);
		while ((*p_str).amount-- > 0)
			*c += write (1, "0", 1);
		ft_putnbrhex_pf(ft_longlong(a_val, sp), sp, c);
	}
	ft_print_p_nbr(a_val, p_str, sp, c);
}

void	ft_print_p_nbr(t_arg a_val, t_flag *p_str, const char **sp, int *c)
{
	if ((*p_str).precision == 1)
	{
		(*p_str).tmp = (*p_str).prec_width;
		(*p_str).tmp_width = (*p_str).width;
		(*p_str).prec_width -= (*p_str).nbr_len;
		if ((*p_str).prec_width < 0)
			(*p_str).prec_width = 0;
		if (ft_longlong(a_val, sp) < 0 || p_str->sign == 1 || p_str->space == 1)
			(*p_str).nbr_sign++;
		(*p_str).width -= ((*p_str).nbr_sign
				+ (*p_str).prec_width + (*p_str).nbr_len);
		while ((*p_str).width-- > 0)
			*c += write(1, " ", 1);
		if (ft_longlong(a_val, sp) < 0 || p_str->sign == 1 || p_str->space == 1)
			ft_print_sign(p_str, ft_longlong(a_val, sp), c);
		while ((*p_str).prec_width-- > 0)
			*c += write(1, "0", 1);
		if (ft_longlong(a_val, sp) != 0)
			ft_putnbrhex_pf(ft_longlong(a_val, sp), sp, c);
		else if ((*p_str).tmp != 0)
			*c += write(1, "0", 1);
		else if ((*p_str).tmp_width != 0)
			*c += write(1, " ", 1);
	}
	ft_print_nbr(a_val, p_str, sp, c);
}

void	ft_print_nbr(t_arg a_val, t_flag *p_str, const char **sp, int *c)
{
	if ((*p_str).zero == 0 && (*p_str).precision == 0)
	{
		(*p_str).width -= (*p_str).nbr_len;
		if (ft_longlong(a_val, sp) < 0)
			(*p_str).width--;
		while ((*p_str).width-- > 0)
			*c += write(1, " ", 1);
		if (ft_longlong(a_val, sp) < 0 || (*p_str).space == 1
			|| (*p_str).sign == 1)
			ft_print_sign(p_str, ft_longlong(a_val, sp), c);
		ft_putnbrhex_pf(ft_longlong(a_val, sp), sp, c);
	}
}
