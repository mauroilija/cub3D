/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:06:52 by abita             #+#    #+#             */
/*   Updated: 2026/04/14 16:31:37 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_line(t_line *map)
{
	map->first_map_line = NULL;
	map->last_map_line = NULL;
	map->is_first_line = 1;
	map->error = 0;
	map->player_count = 0;
	map->map_started = 0;
	map->height = 0;
}

int	skip_whitespace(char *line)
{
	int i;

	i = 0;
	while ((line[i] && line[i] == ' '))
		i++;
	return (i);
}
int is_texture_line(char **line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i][j] == ' ' || line[i][j] == '\t')
		i++;
	if ((line[i][j] == 'N' && line[i][j + 1] == 'O') 
		|| (line[i][j]== 'S' && line[i][j + 1] == 'O')
		|| (line[i][j] == 'W' && line[i][j + 1] == 'E')
		|| (line[i][j] == 'E' && line[i][j + 1] == 'A'))
	{
		if (line[i][j + 2] == ' ' || line[i][j + 2] == '\t')
			return (1);
	}
	return (0);
} 

int is_color_line(char **line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i][j] == ' ' || line[i][j] == '\t')
		i++;
	if (line[i][j] == 'F' || line[i][j] == 'C')
	{
		if (line[i][j + 1] == ' ' || line[i][j + 1] == '\t')
			return (1);
	}
	return (0);
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
