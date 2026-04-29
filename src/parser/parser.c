/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:02:56 by abita             #+#    #+#             */
/*   Updated: 2026/04/29 15:10:27 by abita            ###   ########.fr       */
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
				print_error(PASS_TEXTURE_COLOR), EXIT_FAILURE);
		else
			map->map_flag = true;
	}
	else
		return (print_error(INVALID_LINE), EXIT_FAILURE);
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
		if (map->floor_count == 0 || map->ceiling_count == 0)
			return (print_error(MISSING_COLOR), EXIT_FAILURE);
		if (map->no_count == 0 || map->so_count == 0
			|| map->we_count == 0 || map->ea_count == 0)
			return (print_error(MISSING_TEXTURE), EXIT_FAILURE);
		if (map_parsing(&line[i], map) != EXIT_SUCCESS)
			return (print_error(INVALID_LINE_END), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	parser(char *path, t_map *map)
{
	map->fd = open(path, O_RDONLY);
	if (map->fd == -1)
		return (print_error(CANT_OPEN_FILE), EXIT_FAILURE);
	init_line(map);
	map->line = get_next_line(map->fd);
	while (map->line)
	{
		if (parse_input(map->line, map) != EXIT_SUCCESS)
			return (freedom(map), flush(map), EXIT_FAILURE);
		free(map->line);
		map->line = get_next_line(map->fd);
	}
	flush(map);
	if (!map->map_flag)
		return (print_error(NO_MAP_FOUND), freedom(map), EXIT_FAILURE);
	if (grid_validation(map->grid, map->height, map) != EXIT_SUCCESS)
		return (freedom(map), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	validate_input(t_map *line, int argc, char **argv)
{
	char	*last_dot;

	if (argc < 2)
		return (print_error(NO_MAP_FILE), EXIT_FAILURE);
	if (argc > 2)
		return (print_error(TOO_MANY_ARGS), EXIT_FAILURE);
	if (check_hidden_path(argv[1]) == EXIT_FAILURE)
		return (print_error(HIDDEN_PATH), EXIT_FAILURE);
	last_dot = ft_strrchr(argv[1], '.');
	if (!last_dot || ft_strcmp(last_dot, ".cub") != 0)
		return (print_error(CUB_EXTENSION), EXIT_FAILURE);
	if (parser(argv[1], line) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
