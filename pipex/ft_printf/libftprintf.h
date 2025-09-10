/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:49:28 by samalves          #+#    #+#             */
/*   Updated: 2025/06/24 10:51:15 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>

int	ft_printf(const char *s, ...);
int	ft_putchar(int c);
int	ft_putstr(const char *str);
int	ft_phex(void *ptr);
int	ft_decimal(int i);
int	ft_unsdecimal(unsigned long long i);
int	ft_hexlow(unsigned long long num);
int	ft_hexupp(unsigned long long num);

#endif
