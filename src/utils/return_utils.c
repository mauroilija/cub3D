/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arselabita <arselabita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:29:49 by abita             #+#    #+#             */
/*   Updated: 2026/04/08 19:34:21 by arselabita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_error(const char *msg)
{
	write(STDERR_FILENO, RED, 5);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, RED, 5);
}
void	print_pass(const char *msg)
{
	write(STDERR_FILENO, GREEN, 5);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, GREEN, 5);
}