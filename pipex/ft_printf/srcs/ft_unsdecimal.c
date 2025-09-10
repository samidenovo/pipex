/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsdecimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:01:54 by samalves          #+#    #+#             */
/*   Updated: 2025/06/23 17:10:07 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_unsdecimal(unsigned long long n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len += ft_unsdecimal(n / 10);
	len += ft_putchar((n % 10) + '0');
	return (len);
}
