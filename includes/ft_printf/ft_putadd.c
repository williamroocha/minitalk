/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:01:05 by wiferrei          #+#    #+#             */
/*   Updated: 2023/04/26 16:01:07 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putadd(unsigned long int nbr, long int *chr_total, int x)
{
	if (!nbr)
	{
		ft_putstr("(nil)", chr_total);
		return ;
	}
	if (x == 0)
		ft_putstr("0x", chr_total);
	if (nbr >= 16)
		ft_putadd((nbr / 16), chr_total, ++x);
	ft_putchar(HEX_LOWER[nbr % 16], chr_total);
}
