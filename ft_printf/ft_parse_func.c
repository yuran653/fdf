/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:06:23 by jgoldste          #+#    #+#             */
/*   Updated: 2021/11/14 14:06:26 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isdigit_pf(int str)
{
	if (str >= '1' && str <= '9')
		return (1);
	else
		return (0);
}

void	ft_parse_value(t_flag *p_str, const char **fl)
{
	if (**fl == '0')
	{
		if (*(*fl + 1) == '0')
			*fl += 1;
		(*p_str).zero = 1;
		if (ft_isdigit_pf(*(*fl + 1)) == 1)
		{
			*fl += 1;
			(*p_str).width = ft_atoi(*fl);
			*fl = (*fl + (ft_nbrlen_pf((*p_str).width) - 1));
		}
	}
	if (**fl == '.')
	{
		if (*(*fl + 1) == '0')
			*fl += 1;
		(*p_str).precision = 1;
		if (ft_isdigit_pf(*(*fl + 1)) == 1)
		{
			*fl += 1;
			(*p_str).prec_width = ft_atoi(*fl);
			*fl = (*fl + (ft_nbrlen_pf((*p_str).prec_width) - 1));
		}
	}
}

void	ft_parse_flags(t_flag *p_str, const char **flags)
{
	ft_put_zero_pf(p_str);
	while (ft_strchr_pf(FLAGS_DIGITS, **flags) == 1)
	{
		if (**flags == '-')
			(*p_str).align = 1;
		else if (**flags == '#')
			(*p_str).hash = 1;
		else if (**flags == ' ')
			(*p_str).space = 1;
		else if (**flags == '+')
			(*p_str).sign = 1;
		else if (**flags == '0')
			ft_parse_value(p_str, flags);
		else if (**flags == '.')
			ft_parse_value(p_str, flags);
		else if (ft_isdigit_pf(**flags) == 1)
		{
			(*p_str).width = ft_atoi(*flags);
			*flags = (*flags + (ft_nbrlen_pf((*p_str).width) - 1));
		}
		*flags += 1;
	}
}

void	ft_parse_nbr(t_arg a_val, t_flag *p_str, const char **sp, int *c)
{
	if ((*p_str).precision == 1)
		(*p_str).zero = 0;
	if ((*p_str).sign == 1)
		(*p_str).space = 0;
	if (**sp == 'u')
	{
		(*p_str).space = 0;
		(*p_str).sign = 0;
	}
	if ((*p_str).align == 1)
	{
		(*p_str).zero = 0;
		(*p_str).nbr_len = ft_nbrlen_pf(ft_longlong(a_val, sp));
		ft_print_a_nbr(a_val, p_str, sp, c);
	}
	else
		ft_print_z_nbr(a_val, p_str, sp, c);
}

void	ft_getarg(va_list args, t_arg *a_val, const char **sp)
{
	if (**sp == '%')
		(*a_val).c = '%';
	else if (**sp == 'c')
		(*a_val).c = va_arg(args, int);
	else if (**sp == 's')
		(*a_val).s = va_arg(args, char *);
	else if (**sp == 'd' || **sp == 'i')
		(*a_val).d = va_arg(args, int);
	else if (**sp == 'u' || **sp == 'X' || **sp == 'x')
		(*a_val).u = va_arg(args, unsigned int);
	else if (**sp == 'p')
		(*a_val).p = va_arg(args, unsigned long long);
}
