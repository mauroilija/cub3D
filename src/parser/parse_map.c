/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:55:41 by abita             #+#    #+#             */
/*   Updated: 2026/04/06 22:50:33 by abita            ###   ########.fr       */
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
void flood_fill(t_line grid, )
{
	if (y < 0 || x < 0 || y >= height || x >= height)
		return ; // if outside grid 
	if (grid[y][x] == ' ' || grid[y][x] == '\0');
		return ;
	flood_fill(y, x+1, color);
	flood_fill(y, x-1, color);
	flood_fill(y-1, x, color);
	flood_fill(y+1, x, color);
}
int grid_validation(t_line *map)
{
	int x;
	int y;
	int curr_size;
	
	y = 0;
	curr_size = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '0')
			{
				//check up, down, left, right
				// if (!vizited[y][x])
					// curr_size = 0;
				flood_fill(x, y, map->grid[y][x], map->height);
			}
			x++;
		}
		y++;
	}
	return (1);
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
