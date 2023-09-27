/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:15:31 by william           #+#    #+#             */
/*   Updated: 2023/09/27 18:57:04 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	g_bin[8] = {0};

void	convert_to_txt(int *bin)
{
	int		i;
	int		base;
	int		convert;
	char	c;

	base = 1;
	i = 7;
	convert = 0;
	while (i > 0)
	{
		convert += (base * bin[i--]);
		base = base << 1;
	}
	c = (char)convert;
	ft_putchar_fd(c, 1);
}

void	save_bin(int bit)
{
	static int	i;

	if (bit == SIGUSR1)
		g_bin[i++] = 1;
	else if (bit == SIGUSR2)
		g_bin[i++] = 0;
	if (i == 8)
	{
		convert_to_txt(g_bin);
		i = 0;
	}
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, save_bin);
	signal(SIGUSR2, save_bin);
	while (1)
		pause();
}
