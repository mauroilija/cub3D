/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:55:41 by abita             #+#    #+#             */
/*   Updated: 2026/04/14 17:45:51 by milija-h         ###   ########.fr       */
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

	if (!line) {
		return (1);
	}
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_valid_input(line[i])) {
			printf("line fail\n");
			return (1);
		}
		if (is_player(line[i]))
			map->player_count++;
		i++;
	}
	return (0);
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
char **map_add_line(char **old, char *line)
{
	int		i;
	char	**new;

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
    // printf("here: flood_fill called with y = %d, x = %d\n", y, x);
    // printf("what:\n height - 1: '%d'\n && y: %d\n && x: %d\n && grid[%d]: %d\n", height - 1, y, x, y, ft_strlen(grid[y]));
    
    if (y < 0 || y >= height || x < 0 || x >= (int)ft_strlen(grid[y]))
        return (1);
    // here i check if the map is open by checking for spaces around the '0' cells, if a space then i return;
    if (grid[y][x] == ' ' || grid[y][x] == '\0')
        return (1);
    if (grid[y][x] == '1' || grid[y][x] == '*') // then i have either encountered a wall or i have been at a cell before i just stop and return
        return (0);
    grid[y][x] = '*'; //.. this i just mark the position just visited to let me knw that i have been here before  
    if (flood_fill(grid, y, x + 1, height))
        return (1);
    if (flood_fill(grid, y, x - 1, height))
        return (1);
    if (flood_fill(grid, y + 1, x, height)) 
        return (1);
    if (flood_fill(grid, y - 1, x, height))
        return (1);
    return (0);
}

int grid_validation(char **grid, int height, t_line *map)
{
    int x;
    int y;
    // char **grid_copy;

    y = 0;
    while (y < height)
    {
        x = 0;
        while (grid[y][x])
        {
            // printf("\ngrid[%d][%d] = %c\n", y, x, grid[y][x]);
            // printf("here: \nheight - 1: '%d'\n && y: %d\n && x: %d\n", height - 1, y, x);
            if (grid[y][x] == 'N' || grid[y][x] == 'S' || grid[y][x] == 'E' || grid[y][x] == 'W')
            {
                map->player_x = x;
                map->player_y = y; 
                // printf("player position: x = %d, y = %d\n", player_x, player_y);
            }
            // if (grid[y][x] == '0')
            // {
            //     if (x >= ft_strlen(grid[y - 1]) || x >= ft_strlen(grid[y + 1])) // for uneven rows
            //     {
            //         printf("ERROR: map doest have even\n");
            //         return (1);
            //     }
            //     if ((grid[y][x - 1] == ' ' || grid[y][x - 1] == '\0') ||
            //     (grid[y][x + 1] == ' ' || grid[y][x + 1] == '\0') ||
            //     (grid[y - 1][x] == ' ' || grid[y - 1][x] == '\0') ||
            //     (grid[y + 1][x] == ' ' || grid[y + 1][x] == '\0'))
            //     {
            //         printf("ERROR: map is not closed\n");
            //         return (1);
            //     }
            //     // if ((grid[y][x - 1] == '1') || (grid[y][x + 1] == '1') || 
            //     //     (grid[y - 1][x] == '1') || (grid[y + 1][x] == '1'))
            //     //     {
            //     //         printf("ERROR: map is not valid\n");
            //     //         return (1);
            //     //     }
                // printf("cell [%d][%d] is valid\n", y, x);
            // }
            x++;
        }
        y++;
    }
  
    return (EXIT_SUCCESS);
}
int	parse_map_line(char *line, t_line *map)
{
	int		i;
	char	*clean;
	int ret = 0;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (EXIT_SUCCESS);
	clean = ft_strtrim(&line[i], "\n");
	if (!clean)
		return (ERROR_MALLOC);
	if (is_valid_map(clean, map) != EXIT_SUCCESS)
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

	ret = grid_validation(map->grid, map->height, map);
	if (ret != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	 char **grid_copy = copy_grid(map->grid, map->height);
    grid_copy[map->player_y][map->player_x] = '0';
    if (!flood_fill(grid_copy, map->player_y, map->player_x, map->height))
    {
		return (1);
	}
		//else
    //{
    //    printf("PASSED: map is valid and closed\n");
    //}
	// printf("line: %s\n", line);
	// printf("each line len: %lu\n", ft_strlen(line));
	free(clean);
	clean = NULL;
	free_split(grid_copy);
	grid_copy = NULL;
	return (EXIT_SUCCESS);
}
