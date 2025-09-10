/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexlow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:55:47 by samalves          #+#    #+#             */
/*   Updated: 2025/06/24 10:42:15 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_hexlow(unsigned long long num)
{
	char	*base;
	int		len;

	base = "0123456789abcdef";
	len = 0;
	if (num >= 16)
		len += ft_hexlow(num / 16);
	len += ft_putchar(base[num % 16]);
	return (len);
}
