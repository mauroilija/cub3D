/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:41:07 by abita             #+#    #+#             */
/*   Updated: 2026/04/19 13:36:51 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
	1. The top and bottom row should be only 1's
	2. The first and last position in a row should be 1.
	3. A zero should be surrounded by: 1, 0, N, S, W, E
*/

int grid_validation(char **grid, int height, t_line *map)
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
				if (is_player(grid[y][x]))
				{
					map->player_count++;
					if (map->player_count != 1)
						return (1);
				}
				if (y == 0 || x == 0 || y == height -1 || x == (int)ft_strlen(grid[y]) - 1)
        			return (printf("ERROR: map is open at the borders\n"), 1);
				if (x >= (int)ft_strlen(grid[y - 1]) || x >= (int)ft_strlen(grid[y + 1]))
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

int map_parsing(char *line, t_line *map)
{
	int i;
	char  *clean_line;
	int return_value;

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
	if (grid_validation(map->grid, map->height, map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (free(clean_line), EXIT_SUCCESS);
}
