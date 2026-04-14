/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:41:07 by abita             #+#    #+#             */
/*   Updated: 2026/04/14 20:06:00 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
	1. The top and bottom row should be only 1's
	2. The first and last position in a row should be 1.
	3. A zero should be surrounded by: 1, 0, N, S, W, E
*/

int	is_valid(char line)
{
	return (line == 'N' || line == 'S' || line == 'E' || line == 'W' || line == '1' || line == '0');
}

int	is_player(char line)
{
	return (line == 'N' || line == 'S' || line == 'E' || line == 'W');
}

static int grid_validation(char **grid, int height, t_map *map)
{
    int x;
    int y;

    y = 0;
    while (y < height)
    {
        x = 0;
        while (grid[y][x])
        {

            if (grid[y][x] == '0' || is_player(grid[y][x]))
            {
				if (y == 0 || x == 0 || y == height -1)
        			return (printf("ERROR: map is open at the borders\n"), 1);
				if (x >= ft_strlen(grid[y - 1]) || x >= ft_strlen(grid[y + 1]))
					return (printf("ERROR: map is opened(ragged rows)\n"), 1);
                if (!is_valid(grid[y][x - 1]) || !is_valid(grid[y][x + 1]) || 
					!is_valid(grid[y - 1][x]) || !is_valid(grid[y + 1][x]))
					return (printf("ERROR: map is not closed\n"), 1);
			}
            x++;
        }
        y++;
    }
    return (EXIT_SUCCESS);
}

static char **a_copy_of_grid(char **old, int height)
{
	int i;
	char **new_grid;

	new_grid = (char **)ft_calloc((height + 1), sizeof(char *));
	if (!new_grid)
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

static char **creating_2d_map(char **old, char *line)
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

int map_parsing(char *line, t_map *map)
{
	int i;
	int clean_line;
	int return_value;
	char **grid_copy;

	i = 0;
	return_value = 0;
	while(ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (EXIT_FAILURE);
	clean_line = ft_strtrim(&line[i], "\n");
	if (!clean_line)
		return (ERROR_MALLOC);
	map->grid = creating_2d_map(map->grid, clean_line);
	map->height++;
	return_value = grid_validation(map->grid, map->height, map);
	if (return_value != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	grid_copy = a_copy_of_grid(map->grid, map->height);
	grid_copy[map->player_y][map->player_x] = '0';
	if (!flood_fill(grid_copy, map->player_y, map->player_x, map->height))
        return (1);
	return (free(clean_line), EXIT_SUCCESS);
}
