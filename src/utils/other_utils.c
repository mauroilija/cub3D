/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:29:49 by abita             #+#    #+#             */
/*   Updated: 2026/04/29 12:22:58 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	print_error(const char *msg)
{
// 	write(STDERR_FILENO, RED, 5);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	// write(STDERR_FILENO, RED, 5);
}

int	is_number(char *n)
{
	int	i;

	if (!n || !n[0])
		return (0);
	i = 0;
	while (n[i] == ' ' || n[i] == '\t')
		i++;
	while (n[i])
	{
		if (!ft_isdigit(n[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_all(t_map *map)
{
	if (map->line)
		free(map->line);
	if (map->grid)
		free_split(map->grid);
	free_texture_paths(&map->texture_data);
}

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}
