/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:02:56 by abita             #+#    #+#             */
/*   Updated: 2026/04/27 17:33:42 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static int	checker(int i, char *line, t_map *map)
{
	if (is_texture_line(&line[i], map) == EXIT_SUCCESS)
	{
		if (parse_texture(&line[i], &map->texture_data) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else if (is_color_line(&line[i], map) == EXIT_SUCCESS)
	{
		if (parse_color(&line[i], &map->color_data) != EXIT_SUCCESS)
			return (free_texture_paths(&map->texture_data), EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else if (is_map_line(&line[i]))
	{
		if (map->texture_flag != true || map->color_flag != true)
			return (free_texture_paths(&map->texture_data), 
					print_error("Error\npass texture and or color\n"),
					EXIT_FAILURE);
		else
			map->map_flag = true;
	}
	else
		return (print_error("Error\ninvalid config line\n"), 1);
	return (EXIT_SUCCESS);
}

static int	parse_input(char *line, t_map *map)
{
	int		i;

	i = 0;
	if (!line)
		return (EXIT_FAILURE);
	if (line[i] == '\0' || line[i] == '\n')
		return (EXIT_SUCCESS);
	if (!map->map_flag)
		if (checker(i, line, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (map->map_flag == true)
	{
		if (map->floor_count == 0)
				return (print_error("Error\nmissing F color\n"), 1);
		if (map->ceiling_count == 0)
			return (print_error("Error\nmissing C color"), 1);
		if (map->n_count == 0 || map->s_count == 0 || map->w_count == 0 || map->e_count == 0)
			return (print_error("Error\nmissing a texture"), 1);
		if (map_parsing(&line[i], map) != EXIT_SUCCESS)
			return (print_error("Error\ninvalid line after map\n"),
				EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser(char *path, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("Error\nopening the file\n"), EXIT_FAILURE);
	init_line(map);
	line = get_next_line(fd);
	while (line)
	{
		if (parse_input(line, map) != EXIT_SUCCESS)
			return (free_texture_paths(&map->texture_data), free(line), get_next_line(-1), close(fd), EXIT_FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	get_next_line(-1);
	close(fd);
	if (!map->map_flag)
		return (print_error("Error\nNo map found.\n"), EXIT_FAILURE);
	if (grid_validation(map->grid, map->height, map) != EXIT_SUCCESS)
		return (free_split(map->grid), free_texture_paths(&map->texture_data), free(line), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
