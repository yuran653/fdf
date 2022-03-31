/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chr_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:03:04 by jgoldste          #+#    #+#             */
/*   Updated: 2021/11/14 14:03:06 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_chr(t_arg a_val, t_flag *p_str, int *c)
{
	if ((*p_str).align == 1)
	{
		ft_putchr_pf(a_val.c, c);
		while ((*p_str).width-- > 1)
			*c += write(1, " ", 1);
	}
	else
	{
		while ((*p_str).width-- > 1)
			*c += write(1, " ", 1);
		ft_putchr_pf(a_val.c, c);
	}
}

void	ft_print_per(t_arg a_val, t_flag *p_str, int *c)
{
	if ((*p_str).align == 1)
	{
		ft_putchr_pf(a_val.c, c);
		while ((*p_str).width-- > 1)
			*c += write(1, " ", 1);
	}
	else
	{
		if ((*p_str).zero == 1)
			while ((*p_str).width-- > 1)
				*c += write(1, "0", 1);
		else
			while ((*p_str).width-- > 1)
				*c += write(1, " ", 1);
		ft_putchr_pf(a_val.c, c);
	}
}

void	ft_print_str(t_arg a_val, t_flag *p_str, int *c)
{
	if (a_val.s == NULL)
		a_val.s = "(null)";
	if ((*p_str).precision == 0
		|| (*p_str).prec_width > (int)ft_strlen(a_val.s))
		(*p_str).prec_width = (int)ft_strlen(a_val.s);
	(*p_str).width -= (*p_str).prec_width;
	if ((*p_str).align == 1 && (*p_str).width)
	{
		ft_putstr_pf(a_val.s, (*p_str).prec_width, c);
		while ((*p_str).width-- > 0)
			*c += write(1, " ", 1);
	}
	else if ((*p_str).width)
	{
		while ((*p_str).width-- > 0)
			*c += write(1, " ", 1);
		ft_putstr_pf(a_val.s, (*p_str).prec_width, c);
	}
	else
		ft_putstr_pf(a_val.s, (*p_str).prec_width, c);
}

void	ft_print_ptr(t_arg a_val, t_flag *p_str, const char **sp, int *c)
{
	(*p_str).tmp = ft_hexlen_pf(a_val.p);
	(*p_str).width -= 2;
	if (a_val.p)
		(*p_str).width -= (*p_str).tmp;
	if ((*p_str).align == 1)
	{
		ft_putnbrhex_pf(a_val.p, sp, c);
		if (a_val.p == 0)
			*c += write(1, "0", 1);
		while ((*p_str).width-- > 0)
			*c += write(1, " ", 1);
	}
	else
	{
		if (a_val.p == 0)
			(*p_str).width--;
		while ((*p_str).width-- > 0)
			*c += write(1, " ", 1);
		ft_putnbrhex_pf(a_val.p, sp, c);
		if (a_val.p == 0 && (*p_str).precision == 0)
			*c += write(1, "0", 1);
	}
}

int	ft_strchr_pf(char *s, int c)
{
	while (*s != c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return (1);
}
