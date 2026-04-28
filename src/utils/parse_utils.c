/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:06:52 by abita             #+#    #+#             */
/*   Updated: 2026/04/28 19:05:51 by abita            ###   ########.fr       */
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

int	is_texture_line(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;

	if (line[i] == 'N' && line[i + 1] == 'O'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
	{
		if (map->n_count > 0)
			return (print_error("Error\nduplicate NO texture\n"), EXIT_FAILURE);
		map->n_count++;
		map->texture_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
	{
		if (map->s_count > 0)
			return (print_error("Error\nduplicate SO texture\n"), EXIT_FAILURE);
		map->s_count++;
		map->texture_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
	{
		if (map->w_count > 0)
			return (print_error("Error\nduplicate WE texture\n"), EXIT_FAILURE);
		map->w_count++;
		map->texture_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
	{
		if (map->e_count > 0)
			return (print_error("Error\nduplicate texture\n"), EXIT_FAILURE);
		map->e_count++;
		map->texture_flag = true;
		return (EXIT_SUCCESS);	
	}
	return (EXIT_FAILURE);
}
int	is_color_line(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;

	if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
		if (map->floor_count > 0)
			return (print_error("Error\nduplicate F color\n"), EXIT_FAILURE);
		map->floor_count++;
		map->color_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
		if (map->ceiling_count > 0)
			return (print_error("Error\nduplicate C color\n"), EXIT_FAILURE);
		map->ceiling_count++;
		map->color_flag = true;
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
