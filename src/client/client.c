/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:45:27 by wiferrei          #+#    #+#             */
/*   Updated: 2023/09/27 09:31:46 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	args_check(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3)
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
			ft_putstr_fd("Error: PID must be a number\n", 2);
		i++;
	}
	if (*av[2] == '\0')
		ft_putstr_fd("Error: Empty string\n", 2);
}

void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
		ft_putstr_fd("Message received by server\n", 1);
	else if (signum == SIGUSR2)
		ft_putstr_fd("Message received by server\n", 1);
	else
		ft_putstr_fd("Error: Unknown signal\n", 2);
	exit(0);
}

void	config_sigaction(void)
{
	struct sigaction	sa_newsig;

	sa_newsig.sa_handler = &sig_handler;
	sa_newsig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_newsig, NULL) == -1)
		ft_putstr_fd("Failed to change SIGUSR1's behavior", 2);
	if (sigaction(SIGUSR2, &sa_newsig, NULL) == -1)
		ft_putstr_fd("Failed to change SIGUSR2's behavior", 2);
}

void	send_message(pid_t server_pid, char *message)
{
	unsigned char	c;
	int				nbr_bits;

	while (*message)
	{
		c = *message;
		nbr_bits = 8;
		while (nbr_bits--)
		{
			if (c & 0b10000000)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			usleep(50);
			c <<= 1;
		}
		message++;
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;

	args_check(ac, av);
	server_pid = ft_atoi(av[1]);
	ft_printf("Client PID: %d\n", getpid());
	config_sigaction();
	send_message(server_pid, av[2]);
	while (1)
	{
		pause();
	}
	return (0);
}
