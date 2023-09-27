/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:45:27 by wiferrei          #+#    #+#             */
/*   Updated: 2023/09/27 18:57:22 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	send_bit(char *txt, int pid_id)
{
	int		i;
	int		base;
	char	ch;

	i = -1;
	while (txt[++i])
	{
		base = 128;
		ch = txt[i];
		while (base > 0)
		{
			if (ch >= base)
			{
				kill(pid_id, SIGUSR1);
				ch -= base;
			}
			else
				kill(pid_id, SIGUSR2);
			base = base >> 1;
			usleep(250);
		}
	}
}

int	main(int ac, char **av)
{
	if (ft_isdigit(av[1] == 0))
	{
		ft_putstr_fd("Error: PID must be a number\n", 2);
		return (0);
	}
	else
	{
		if (ac == 3)
			send_bit(av[2], ft_atoi(av[1]));
		else
			ft_printf("(Error) Try ./client <PID> <MSG>\n");
	}
	return (0);
}
