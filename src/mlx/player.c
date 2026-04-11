/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:00:28 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/11 21:58:40 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//tell us where the player initially points to
static void	get_direction(char cell, t_player *player)
{
	if (cell == 'N')
	{
		player->x_direction = 0.0f; 
		player->y_direction = -1.0f;
	}
	if (cell == 'S')
	{
		player->x_direction = 0.0f;
		player->y_direction = 1.0f;
	}
	if (cell == 'W')
	{
		player->x_direction = -1.0f;
		player->y_direction = 0.0f;
	}
	if (cell == 'E')
	{
		player->x_direction = 1.0f;
		player->y_direction = 0.0f;
	}
}

static void	get_init_positions(t_player *player, char **map)
{
	size_t	x;
	size_t	y;
	char	cell;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			cell = map[y][x];
			if (cell == 'N' || cell == 'S' || cell == 'W' || cell == 'E')
			{
				player->x_position = (float)x + 0.5f;
				player->y_position = (float)y + 0.5f;
				get_direction(cell, player);
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_player *player, t_line *map)
{
	get_init_positions(player, map->grid);
	//The camera plane (planeX, planeY) is a vector perpendicular to direction,
	//and its length determines the FOV.
	player->fov = 0.66;
	player->plane_len = 1.0 * tan(33); // plane_len and fov are initially same
	player->plane_x = -player->y_direction * 0.66;
	player->plane_y = player->x_direction * 0.66;
	player->dot_product = player->x_direction * player->plane_x +
						player->y_direction * player->plane_y;
	// The camera plane must be perpendicular to the direction vector (hence why the dot)
	player->step_x = 0;
	player->step_y = 0;
	player->ray_direction_x = 0.0;
	player->ray_direction_y = 0.0;
	player->decimal_x = 0.0;
	player->decimal_x = 0.0;
	player->d_next_tile_x = 0.0; //distance on a ray to the next tile
	player->d_next_tile_y = 0.0;
	player->side_dist_x = 0.0;
	player->side_dist_y = 0.0;
	player->map_position_x = 0;
	player->map_position_y = 0;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->key_up = false;
}
