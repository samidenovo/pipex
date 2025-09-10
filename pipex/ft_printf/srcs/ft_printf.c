/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:22:09 by samalves          #+#    #+#             */
/*   Updated: 2025/06/24 10:46:00 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_datatype(char s, va_list args)
{
	int	len;

	len = 0;
	if (s == 'c')
		len = ft_putchar(va_arg(args, int));
	else if (s == 's')
		len = ft_putstr(va_arg(args, char *));
	else if (s == 'p')
		len = ft_phex(va_arg(args, void *));
	else if (s == 'd' || s == 'i')
		len = ft_decimal(va_arg(args, int));
	else if (s == 'u')
		len = ft_unsdecimal(va_arg(args, unsigned int));
	else if (s == 'x')
		len = ft_hexlow(va_arg(args, unsigned int));
	else if (s == 'X')
		len = ft_hexupp(va_arg(args, unsigned int));
	else if (s == '%')
		len = ft_putchar('%');
	return (len);
}

static int	ft_parse(const char *s, va_list args)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			len += ft_datatype(s[i], args);
			i++;
		}
		else
		{
			write(1, &s[i], 1);
			len++;
			i++;
		}
	}
	return (len);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		len;

	va_start(args, s);
	len = ft_parse(s, args);
	va_end(args);
	return (len);
}
