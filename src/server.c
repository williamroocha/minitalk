/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei < wiferrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:02:27 by wiferrei          #+#    #+#             */
/*   Updated: 2023/09/18 18:44:20 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_printf("Server PID: %d\n", server_pid);
}
