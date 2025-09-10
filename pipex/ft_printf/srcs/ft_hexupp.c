/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexupp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:23:27 by samalves          #+#    #+#             */
/*   Updated: 2025/06/24 10:42:31 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_hexupp(unsigned long long num)
{
	char	*base;
	int		len;

	base = "0123456789ABCDEF";
	len = 0;
	if (num >= 16)
		len += ft_hexupp(num / 16);
	len += ft_putchar(base[num % 16]);
	return (len);
}
