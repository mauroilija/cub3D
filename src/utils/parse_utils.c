/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:06:52 by abita             #+#    #+#             */
/*   Updated: 2026/04/29 12:23:20 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	init_line(t_map *map)
{
	map->player_count = 0;
	map->height = 0;
	map->texture_flag = false;
	map->color_flag = false;
	map->map_flag = false;
	map->color_data.ceiling_color = -1;
	map->color_data.floor_color = -1;
}

int	skip_whitespace(char *line)
{
	int	i;

	i = 0;
	while ((line[i] && line[i] == ' '))
		i++;
	return (i);
}

int	is_valid_input(char line)
{
	return (line == SPACE || line == WALL || line == NORTH || line == SOUTH
		|| line == EAST || line == WEST || line == ' ' || line == '\t');
}

int	is_valid(char line)
{
	return (line == 'N' || line == 'S' || line == 'E' || line == 'W'
		|| line == '1' || line == '0');
}
