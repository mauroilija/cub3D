/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:00:49 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/13 20:06:58 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_wall_strip(t_data *data, t_player *player, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
	int	y;

	line_height = (int)(HEIGHT / player->perp_wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	if (player->side == 0)
		color = 0x00FF00;
	else 
		color = 0x007700;
	y = draw_start;
	while (y < draw_end)
	{
		my_pixel_put(data->img, x, y, color);
		y++;
	}
}
