/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:02:56 by abita             #+#    #+#             */
/*   Updated: 2026/04/22 12:45:22 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static int checker(int i, char *line, t_line *map)
{
	if (is_texture_line(&line[i]))
	{
		if (parse_texture(&line[i], &map->t_data) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else if (is_color_line(&line[i]))
	{
		if (parse_color(&line[i], &map->c_data) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else if (is_map_line(&line[i]))
		map->map_started = 1;
	else
		return(print_error("ERROR: invalid config line\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	parse_input(char *line, t_line *map)
{
	int		i;

	i = 0;
	if (line[i] == '\0' || line[i] == '\n')
	{
		if (map->map_started)
			return (printf("ERROR: empty line in map\n"), EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!map->map_started)
		checker(i, line, map);
	if (map->map_started)
	{
		if (map_parsing(&line[i], map) != EXIT_SUCCESS)
			return (printf("ERROR: invalid line after map\n"), EXIT_FAILURE);		
	}
	return (EXIT_SUCCESS);
}

int	parser(char *path, t_line *map)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("Error: opening the file\n"), ERROR_FD);
	init_line(map);
	while ((line = get_next_line(fd)))
	{
		if (parse_input(line, map) != EXIT_SUCCESS)
		{
			free(line);
			get_next_line(-1);
			close(fd);
			return (EXIT_FAILURE);
		}
		free(line);
	}
	get_next_line(-1);
	close(fd);
	if (!map->map_started)
		return (print_error("ERROR: No map found.\n"), EXIT_FAILURE);
	if (grid_validation(map->grid, map->height, map) != EXIT_SUCCESS)
		return (free_split(map->grid), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
