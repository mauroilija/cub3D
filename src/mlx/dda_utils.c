/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:53:46 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/11 22:04:36 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//exact position in the fov line in a normalized way
//instead of working with the with for example a 320 pixels wide screen
//left would be -1 middle 0 right 1
//in this case we are talking about the x-axis (horizontally) strictly
void	camera_position(t_player *player, int x)
{
	player->camera_x = 2.0f * x / (float)WIDTH - 1.0f;
	player->ray_direction_x = player->x_direction + player->plane_x *
		player->camera_x;
	player->ray_direction_y = player->y_direction + player->plane_y *
		player->camera_x;
}
// we we will compute the exact position of our player within the given
//cell, as we know our map is a combination of cell, each with a x and y
//axis position
//what we do here is we try to find the fractional part of the x/y position
// we do that by taking the integer part of the float position and subtracting
//it by its decimal part
// so if position is 1.12
// we 1 - 0.12
void	exact_position_in_cell(t_player *player)
{
	player->map_position_x = (int)player->x_position;
	player->map_position_y = (int)player->y_position;
	player->decimal_x = player->x_position - player->map_position_x;
	player->decimal_y = player->y_position - player->map_position_y;
}
//further check where the formula comes from
void	distance_to_next_tile(t_player *player)
{
	if (player->ray_direction_x == 0)
		player->d_next_tile_x = 1e30;
	else
		player->d_next_tile_x = fabs(1.0 / player->ray_direction_x);
	if (player->ray_direction_y == 0)
		player->d_next_tile_y = 1e30;
	else
		player->d_next_tile_y = fabs(1 / player->ray_direction_y);
}

//distance of a step is by default 1 or -1
//if its 1, it means we are facing in the direction in which the given axis is
//affected
void	define_step_len(t_player *player)
{
	if (player->x_direction >= 0)
	{
		player->step_x = 1;
		player->side_dist_x = (player->x_position - player->map_position_x)
		* player->d_next_tile_x;
	}
	else
	{
		player->step_x = -1;
		player->side_dist_x = (player->map_position_x + 1 - player->x_position) *
		player->d_next_tile_x;
	}
	if (player->y_direction >= 0)
	{
		player->step_y = 1;
		player->side_dist_y = (player->y_position - player->map_position_y)
		* player->d_next_tile_y;
	}
	else
	{
		player->step_y = -1;
		player->side_dist_y = (player->map_position_y + 1 - player->y_position) *
		player->d_next_tile_y;
	}
}

