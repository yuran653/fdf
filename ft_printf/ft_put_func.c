/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:12:51 by jgoldste          #+#    #+#             */
/*   Updated: 2021/11/14 14:12:53 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_zero_pf(t_flag *p_str)
{
	(*p_str).align = 0;
	(*p_str).zero = 0;
	(*p_str).precision = 0;
	(*p_str).hash = 0;
	(*p_str).space = 0;
	(*p_str).sign = 0;
	(*p_str).width = 0;
	(*p_str).prec_width = 0;
	(*p_str).nbr_len = 0;
	(*p_str).nbr_sign = 0;
	(*p_str).amount = 0;
	(*p_str).tmp = 0;
	(*p_str).tmp_width = 0;
}

long long	ft_longlong(t_arg a_val, const char **sp)
{
	long long	num;

	if (**sp == 'd' || **sp == 'i')
		num = (long long)a_val.d;
	if (**sp == 'u' || **sp == 'x' || **sp == 'X')
		num = (long long)a_val.u;
	return (num);
}

void	ft_putchr_pf(char s, int *c)
{
	*c += write(1, &s, 1);
}

void	ft_putstr_pf(char *str, int width, int *c)
{
	while (width--)
		*c += write(1, str++, 1);
}

void	ft_putzero_hex(long long hex, t_flag *p_str, const char **sp, int *c)
{
	if (hex != 0)
	{
		if ((*p_str).precision == 1 && (*p_str).tmp_width == 0
			&& (*p_str).align == 0)
			while ((*p_str).width-- > 0)
				*c += write(1, " ", 1);
		ft_putnbrhex_pf(hex, sp, c);
	}
	else
		(*p_str).nbr_len = 0;
}
