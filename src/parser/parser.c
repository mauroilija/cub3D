/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:02:56 by abita             #+#    #+#             */
/*   Updated: 2026/04/14 20:34:20 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

////////////////
// here i validate the first and last rows to check if it
// contains 1 or also spaces,
// if it contains smth else than it frees and displays error,
//	that the map is not valid
////////////////

static int	parse_input(char *line, t_line *map, t_color_data *c_data, t_texture_data *t_data)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	if (!map->map_started)
	{
		if (is_texture_line(&line[i]))
			return (parse_texture(&line[i], t_data));
		if (is_color_line(&line[i]))
			return (parse_color(&line[i], c_data));
		if (is_map_line(&line[i]))
			map->map_started = 1;
	}
	return (map_parsing(&line[i], map));
}

int	parser(char *path, t_line *map, t_color_data *c_data, t_texture_data *t_data)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("Error: opening the file\n"), ERROR_FD);
	init_line(map);
	while ((line = get_next_line(fd)))
	{
		if (parse_input(line, map, c_data, t_data) != EXIT_SUCCESS)
		{
			free(line);
			line = NULL;
			continue;
		}
		free(line);
	}
	get_next_line(-1);
	close(fd);
	if (!map->map_started)
		return (print_error("ERROR: No map found.\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
