/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:48:35 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/29 13:39:28 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub.h"

static void	draw_ceiling(t_data *data, int x, int y, int draw_start)
{
	while (y < draw_start)
	{
		my_pixel_put(data->img, x, y, data->map->color_data.ceiling_color);
		y++;
	}
}

static	void	draw_floor(t_data *data, int x, int y, int height)
{
	while (y < height)
	{
		my_pixel_put(data->img, x, y, data->map->color_data.floor_color);
		y++;
	}
}

void	draw_floor_ceiling(t_data *data, t_player *player, int x)
{
	int	wall_height;
	int	draw_start;
	int	draw_end;
	int	y;

	wall_height = (int)(HEIGHT / player->perp_wall_dist);
	draw_start = -wall_height / 2 + HEIGHT / 2;
	draw_end = wall_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	y = 0;
	draw_ceiling(data, x, y, draw_start);
	draw_textured_column(data, x, wall_height);
	y = draw_end;
	draw_floor(data, x, y, HEIGHT - draw_end);
}
