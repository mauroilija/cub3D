/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:00:28 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/29 15:10:03 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub.h"

//tell us where the player initially points to
static void	get_direction(char cell, t_player *player)
{
	if (cell == 'N')
	{
		player->dir_x = 0.0f;
		player->dir_y = -1.0f;
	}
	if (cell == 'S')
	{
		player->dir_x = 0.0f;
		player->dir_y = 1.0f;
	}
	if (cell == 'W')
	{
		player->dir_x = -1.0f;
		player->dir_y = 0.0f;
	}
	if (cell == 'E')
	{
		player->dir_x = 1.0f;
		player->dir_y = 0.0f;
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
				player->pos_x = (float)x + 0.5f;
				player->pos_y = (float)y + 0.5f;
				get_direction(cell, player);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_keys(t_player *player)
{
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->key_up = false;
	player->a_key = false;
	player->d_key = false;
}

void	init_player(t_player *player, t_map *map)
{
	ft_bzero(player, sizeof(t_player));
	get_init_positions(player, map->grid);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
	player->camera_x = 0.0;
	player->step_x = 0;
	player->step_y = 0;
	player->ray_dir_x = 0.0;
	player->ray_dir_y = 0.0;
	player->delta_dist_x = 0.0;
	player->delta_dist_y = 0.0;
	player->side_dist_x = 0.0;
	player->side_dist_y = 0.0;
	player->map_x = 0;
	player->map_y = 0;
	player->perp_wall_dist = 0.0;
	player->wall_x = 0.0;
	player->texture_y = 0;
	player->move_speed = 0;
	player->rot_speed = 0;
	init_keys(player);
}
