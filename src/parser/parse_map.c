/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arselabita <arselabita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:55:41 by abita             #+#    #+#             */
/*   Updated: 2026/04/08 19:40:45 by arselabita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

////////////////
// so, literally,
//	what i do is that i created these 2 variables first and last row,
// to keep track in case these rows are other than 1s. They should always
// be 1 nontheless
// so what i do, i check for each char, and if the first_map_line is empty,
// then add only the first line
// in case we have:
// 		00000000
// 		00000000
// 		11111111
// here our first_map_line will be: 00000000
// where as the last_map_line will just be overwritten for each iteration
// until it reaches the end
// and as a result our last_map_line will be: 11111111
////////////////

int	is_valid_map(char *line, t_line *map)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_valid_input(line[i]))
			return (0);
		if (is_player(line[i]))
			map->player_count++;
		i++;
	}
	return (1);
}

int	is_valid_row(char *line, t_line *map)
{
	int	len;

	(void)map;
	if (!line)
		return (0);
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	// printf("len: %i\n", len);
	if (line[0] != WALL)
		return (0);
	if (line[len - 1] != WALL)
		return (0);
	// printf("last row: %s", map->last_map_line);
	return (1);
}
char **copy_grid(char **old, int height)
{
	int i;
	char **new_grid;

	new = (char **)ft_calloc((height + 1), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < height)
	{
		new_grid[i] = ft_strdup(old[i]);
		i++;
	}
	new_grid[height] = NULL;
	return (new_grid);
}
char **map_add_line(char **old, char *line)
{
	int i;
	char **new;

	i = 0;
	while (old && old[i])
		i++;
	new = (char **)ft_calloc((i + 2), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i++] = ft_strdup(line);
	new[i] = NULL;
	free(old);
	return (new);
}
int flood_fill(char **grid, int y, int x, int height)
{
	if (y < 0 || x < 0 || y >= height || x >= ft_strlen(grid[y]))
		return (1);
	if (grid[y][x] == ' ' || grid[y][x] == '\0');
		return (1);
	if (grid[y][x] == '1' || grid[y][x] == '*')
		return (0);
	grid[y][x] = '*'
    if (flood_fill(grid, y, x + 1, height))
        return (1);;
    if (flood_fill(grid, y, x - 1, height)) 
        return (1);
    if (flood_fill(grid, y + 1, x, height))
        return (1);
    if (flood_fill(grid, y - 1, x, height))
        return (1);
	return (0);
}
int grid_validation(t_line *map)
{
	int x;
	int y;
	char **grid_copy;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			// printf("\ngrid[%d][%d] = %c\n", y, x, grid[y][x]);
			if (grid[y][x] == 'N' || grid[y][x] == 'S' || grid[y][x] == 'W' || grid[y][x] == 'E')
			{
				map->player_x = x;
				map->player_y = y;
			}	
			x++;
		}
		y++;
	}
	grid_copy = copy_grid(grid, height);
	grid_copy[map->player_y][map->player_x] = '0';
	if (flood_fill(grid_copy, map->player_y, map->player_x, map->height))
	{
		print_error("ERROR: map is not closed\n");
		return (1);
	}
	else
	{
		print_pass("PASSED: map is valid and closed");
		return (0);
	}
	return (0);
}
int	parse_map_line(char *line, t_line *map)
{
	int		i;
	char	*clean;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (EXIT_SUCCESS);
	clean = ft_strtrim(&line[i], "\n");
	if (!clean)
		return (ERROR_MALLOC);
	if (!is_valid_map(clean, map))
		map->error = 1;
	
	if (map->is_first_line)
	{
		map->first_map_line = ft_strdup(clean);
		map->is_first_line = 0;
	}
	free(map->last_map_line);
	map->last_map_line = ft_strdup(clean);
	if (!is_valid_row(clean, map))
		map->error = 1;
	map->grid = map_add_line(map->grid, clean);
	map->height++;

	grid_validation(map);
	// printf("line: %s\n", line);
	// printf("each line len: %lu\n", ft_strlen(line));
	return (free(clean), EXIT_SUCCESS);
}
