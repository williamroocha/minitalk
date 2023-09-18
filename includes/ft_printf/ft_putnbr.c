/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:51:14 by wiferrei          #+#    #+#             */
/*   Updated: 2023/04/26 15:51:16 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nbr, long int *chr_total)
{
	if (nbr == -2147483648)
	{
		ft_putstr("-2147483648", chr_total);
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar('-', chr_total);
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10, chr_total);
		ft_putnbr(nbr % 10, chr_total);
	}
	else
		ft_putchar(nbr + '0', chr_total);
}
