/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:00:28 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/10 12:42:00 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	player->fov = 0.66;
	player->plane_len = 1.0 * tan(33); // plane_len and fov are initially same
	player->plane_x = -player->y_direction * 0.66;
	player->plane_y = player->x_direction * 0.66;
	player->dot_product = player->x_direction * player->plane_x +
						player->y_direction * player->plane_y;
	// The camera plane must be perpendicular to the direction vector (hence why the dot)
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->key_up = false;
}

void	draw_player(t_data *data, t_player *player)
{
	for (int dx=-1; dx<=1; dx++)
	{
    	for (int dy=-1; dy<=1; dy++)
        	my_pixel_put(data->img, player->x_position + dx, player->y_position + dy, 0xFF0000);
	}
}
