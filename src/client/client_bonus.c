/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:20:22 by wiferrei          #+#    #+#             */
/*   Updated: 2023/09/30 21:19:49 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

int	ft_str_is_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_send_bit(unsigned int c, int pid_id)
{
	int	bit;

	bit = -1;
	while (++bit < 8)
	{
		if ((c >> bit & 1) && kill(pid_id, SIGUSR1) == -1)
			ft_error_exit("Error: Failed to send SIGUSR1 signal");
		else if (!(c >> bit & 1) && kill(pid_id, SIGUSR2) == -1)
			ft_error_exit("Error: Failed to send SIGUSR2 signal");
		usleep(250);
	}
}

void	ft_handler(int signal)
{
	if (signal == SIGUSR2)
	{
		ft_putstr_fd("Message received\n", 1);
		exit(0);
	}
}

int	main(int ac, char **av)
{
	int	i;

	i = -1;
	if (!ft_str_is_digit(av[1]))
	{
		ft_error_exit("(Error) PID must be a number\n");
		return (EXIT_FAILURE);
	}
	if (kill(ft_atoi(av[1]), 0) == -1)
		ft_error_exit("Error: Invalid PID or Process not running");
	if (ac == 3)
	{
		signal(SIGUSR2, ft_handler);
		while (av[2][++i])
			ft_send_bit(av[2][i], ft_atoi(av[1]));
		ft_send_bit(av[2][i], ft_atoi(av[1]));
		while (1)
			pause();
	}
	else
		ft_error_exit("(Error) Try ./client <PID> <MSG>\n");
	return (EXIT_SUCCESS);
}
