/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:45:27 by wiferrei          #+#    #+#             */
/*   Updated: 2023/09/22 09:18:18 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	check_error_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3)
		ft_error_handler("Wrong number of arguments");
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
			ft_error_handler("Invalid PID");
		i++;
	}
	if (av[2] == NULL)
		ft_error_handler("Invalid message");
}

void	send_message(pid_t sv_pid, char *msg)
{
	unsigned char	c;
	int				nbr_bits;

	while (*msg)
	{
		c = *msg;
		nbr_bits = 8;
		while (nbr_bits--)
		{
			if (c & 0b10000000)
				kill(sv_pid, SIGUSR1);
			else
				kill(sv_pid, SIGUSR2);
			usleep(50);
			c <<= 1;
		}
		msg++;
	}
}

void	handle_sigusr(int signum)
{
	if (signum == SIGUSR2)
		ft_printf("Character has been successfully received!\n");
}

void	configure_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigusr;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_error_handler("Failed to configure SIGUSR1\n");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error_handler("Failed to configure SIGUSR2\n");
}

int	main(int ac, char **av)
{
	pid_t	sv_pid;

	check_error_args(ac, av);
	sv_pid = ft_atoi(av[1]);
	ft_printf("Client PID: %d\n", (int)getpid());
	configure_sigaction();
	ft_printf("Sending message: %s\n", av[2]);
	send_message(sv_pid, av[2]);
	while (1)
	{
		pause();
	}
	return (EXIT_SUCCESS);
}
