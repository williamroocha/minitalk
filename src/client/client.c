/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:45:27 by wiferrei          #+#    #+#             */
/*   Updated: 2023/09/28 20:05:13 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

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

void	send_char_bit(char ch, int pid_id)
{
	int	base;

	base = 128;
	while (base > 0)
	{
		if (ch >= base)
		{
			if (kill(pid_id, SIGUSR1) == -1)
				error_exit("Error sending SIGUSR1");
			ch -= base;
		}
		else
		{
			if (kill(pid_id, SIGUSR2) == -1)
				error_exit("Error sending SIGUSR2");
		}
		base = base >> 1;
		usleep(250);
	}
}

void	send_bit(char *txt, int pid_id)
{
	int	i;

	i = -1;
	while (txt[++i])
		send_char_bit(txt[i], pid_id);
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_printf("(Error) Try ./client <PID> <MSG>\n");
		return (EXIT_FAILURE);
	}
	if (!ft_str_is_digit(av[1]))
	{
		ft_putstr_fd("Error: PID must be a number\n", 2);
		return (EXIT_FAILURE);
	}
	send_bit(av[2], ft_atoi(av[1]));
	return (EXIT_SUCCESS);
}
