/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:06:52 by abita             #+#    #+#             */
/*   Updated: 2026/04/23 20:57:14 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	init_line(t_line *map)
{
	map->player_count = 0;
	map->height = 0;
	map->texture_flag = false;
	map->color_flag = false;
	map->map_flag = false;
}

int	skip_whitespace(char *line)
{
	int	i;

	i = 0;
	while ((line[i] && line[i] == ' '))
		i++;
	return (i);
}

int	is_texture_line(char *line, t_line *map)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if ((line[i] == 'N' && line[i + 1] == 'O')
		|| (line[i] == 'S' && line[i + 1] == 'O')
		|| (line[i] == 'W' && line[i + 1] == 'E')
		|| (line[i] == 'E' && line[i + 1] == 'A'))
	{
		map->texture_flag = true;
		if (line[i + 2] == ' ' || line[i + 2] == '\t')
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	is_color_line(char *line, t_line *map)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'F' || line[i] == 'C')
	{
		map->color_flag = true;
		if (line[i + 1] == ' ' || line[i + 1] == '\t')
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
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
