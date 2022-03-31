/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:15:58 by jgoldste          #+#    #+#             */
/*   Updated: 2021/11/14 14:16:00 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_flags(t_arg a_val, t_flag *p_str, const char **sp, int *c)
{
	if (**sp == 'c')
		ft_print_chr(a_val, p_str, c);
	if (**sp == '%')
		ft_print_per(a_val, p_str, c);
	if (**sp == 'p')
		ft_print_ptr(a_val, p_str, sp, c);
	if (**sp == 's')
		ft_print_str(a_val, p_str, c);
	if (**sp == 'd' || **sp == 'i' || **sp == 'u')
		ft_parse_nbr(a_val, p_str, sp, c);
	if (**sp == 'x' || **sp == 'X')
		ft_parse_hex(a_val, p_str, sp, c);
}

int	ft_printf(const char *str, ...)
{
	int		c;
	va_list	args;
	t_flag	p_str;
	t_arg	a_val;

	c = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1) != '\0')
		{
			str++;
			ft_parse_flags(&p_str, &str);
			ft_getarg(args, &a_val, &str);
			ft_print_flags(a_val, &p_str, &str, &c);
		}
		else
			c += write(1, str, 1);
		str++;
	}
	va_end(args);
	return (c);
}
