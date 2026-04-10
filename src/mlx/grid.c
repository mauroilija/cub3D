/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:52:18 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/10 15:00:03 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_square(t_data *data, float position_x, float position_y,
					size_t tile_size, int color)
{
	size_t	x;
	size_t	y;
	float	pixel_x;
	float	pixel_y;

	y = 0;
	while (y < tile_size)
	{
		x = 0;
		while (x < tile_size)
		{
			pixel_x = position_x + x;
			pixel_y = position_y + y;
			my_pixel_put(data->img, pixel_x, pixel_y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_data *data, t_player *player, char **map)
{
	size_t	y;
	size_t	x;
	char	c;
	int		color;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (c == '1')
				color = 0x00FF00;
			else if(c == '0')
				color = 0xFFFFFF;
			player->x_position = x * TILE_SIZE;
			player->y_position = y * TILE_SIZE;
			draw_square(data, player->x_position, player->y_position, TILE_SIZE, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data, t_player *player)
{
	for (int dx=-1; dx<=1; dx++)
	{
    	for (int dy=-1; dy<=1; dy++)
        	my_pixel_put(data->img, player->x_position + dx, player->y_position + dy, 0xFF0000);
	}
}

void	draw_player_direction(t_data *data, t_player *player, int tile_size)
{
	float	step;
	float	max_length;
	float	cur_x;
	float	cur_y;
	int		screen_x;
	int		screen_y;

	step = 0.1f;
	max_length = 2.0f;
	cur_x = player->x_position;
	cur_y = player->y_position;
	while (step < max_length)
	{
		cur_x = player->x_position + player->x_direction * step;
		cur_y = player->y_position + player->y_direction * step;
		screen_x = (int)(cur_x * tile_size);
		screen_y = (int)(cur_y * tile_size);
		my_pixel_put(data->img, screen_x, screen_y, 0xFF0000); // red
		step += 0.1f;
	}
}