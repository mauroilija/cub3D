/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:00:57 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/13 20:21:36 by milija-h         ###   ########.fr       */
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
		texture_column(player, WIDTH);
		draw_wall_strip(data, player, x);
		x++;
	}
}