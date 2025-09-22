/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:03:42 by samalves          #+#    #+#             */
/*   Updated: 2025/06/23 15:06:01 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_phex(void *ptr)
{
	int			len;
	uintptr_t	address;

	len = 0;
	if (ptr == NULL)
	{
		len = 5;
		write(1, "(nil)", len);
		return (len);
	}
	address = (uintptr_t)ptr;
	len += write(1, "0x", 2);
	len += ft_hexlow(address);
	return (len);
}
