/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:24:06 by wiferrei          #+#    #+#             */
/*   Updated: 2023/04/27 09:16:05 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

# define HEX_UPPER "0123456789ABCDEF"
# define HEX_LOWER "0123456789abcdef"

int		ft_printf(const char *str, ...);
void	ft_types(char *str, va_list args, int i, long int *chr_total);
void	ft_putchar(char c, long int *chr_total);
void	ft_puthexa(unsigned int nbr, long int *chr_total, int uporlow);
void	ft_putadd(unsigned long int nbr, long int *chr_total, int x);
void	ft_putnbr(int nbr, long int *chr_total);
void	ft_putstr(char *str, long int *chr_total);
void	ft_unsgint(unsigned int nbr, long int *chr_total);
#endif