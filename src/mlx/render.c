/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:00:57 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/14 18:42:38 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	render_frame(t_data *data, t_line *map, t_player *player)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		camera_position(player, x);
		advance_to_next_grid(player, map->grid);
		perpendicular_wall_distance(player);
		contact_position(player);
		texture_column(player, player->texture_x);
		draw_wall_strip(data, player, x);
		x++;
	}
}

int	render_loop(void *param)
{
	t_data *data;

	data = (t_data *)param;
	render_frame(data, data->line, data->player);
	return (0);
}