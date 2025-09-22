/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:16:53 by samalves          #+#    #+#             */
/*   Updated: 2025/06/23 17:14:29 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putstr(const char *str)
{
	int	len;

	len = 0;
	if (!str)
	{
		len = 6;
		write(1, "(null)", len);
		return (len);
	}
	while (str[len])
		write(1, &str[len++], 1);
	return (len);
}
