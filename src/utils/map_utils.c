/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:56:33 by abita             #+#    #+#             */
/*   Updated: 2026/04/14 17:43:04 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_valid_input(char line)
{
	//printf("current char: %c\n", line);
	return (line == SPACE || line == WALL || line == NORTH || line == SOUTH
		|| line == EAST || line == WEST || line == ' ' || line == '\t');
}
int	is_player(char line)
{
	return (line == NORTH || line == SOUTH || line == EAST || line == WEST);
}

int	is_all_ones(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != WALL && !ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
