/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:02:02 by wiferrei          #+#    #+#             */
/*   Updated: 2023/04/26 16:02:04 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthexa(unsigned int nbr, long int *chr_total, int loworup)
{
	if (nbr >= 16)
		ft_puthexa(nbr / 16, chr_total, loworup);
	if (loworup)
		ft_putchar(HEX_UPPER[nbr % 16], chr_total);
	else
		ft_putchar(HEX_LOWER[nbr % 16], chr_total);
}
