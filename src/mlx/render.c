/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:00:57 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/14 20:45:53 by milija-h         ###   ########.fr       */
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
		exact_position_in_cell(player);
		distance_to_next_tile(player);
		define_step_len(player);
		advance_to_next_grid(player, map->grid);
		perpendicular_wall_distance(player);
		contact_position(player);
		texture_column(player, 64);
		draw_wall_strip(data, player, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	render_loop(void *param)
{
	t_data *data;

	data = (t_data *)param;
	render_frame(data, data->line, data->player);
	return (0);
}