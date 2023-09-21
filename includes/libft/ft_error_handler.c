/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:22:10 by wiferrei          #+#    #+#             */
/*   Updated: 2023/09/21 09:26:07 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error_handler(char *message)
{
	ft_putstr_fd(STDERR_FILENO, "Error: ", 2);
	ft_putstr_fd(STDERR_FILENO, message, 2);
	ft_putstr_fd(STDERR_FILENO, "\n", 2);
	exit(EXIT_FAILURE);
}
