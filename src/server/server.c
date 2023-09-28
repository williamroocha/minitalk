/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:15:31 by william           #+#    #+#             */
/*   Updated: 2023/09/28 19:56:12 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	g_bin[8] = {0};

void	signal_error(int sig)
{
	const char	*msg;

	msg = "Error: Failed to set signal handler.\n";
	(void)sig;
	ft_putstr_fd((char *)msg, 2);
	exit(EXIT_FAILURE);
}

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
	if (signal(SIGUSR1, save_bin) == SIG_ERR)
		signal_error(SIGUSR1);
	if (signal(SIGUSR2, save_bin) == SIG_ERR)
		signal_error(SIGUSR2);
	while (1)
		usleep(100);
}
