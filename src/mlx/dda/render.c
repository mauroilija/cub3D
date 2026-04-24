/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:00:57 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/24 16:56:33 by milija-h         ###   ########.fr       */
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
		color = 0xA9A9A9;
	else
		color = 0xFFFFFF;
	y = draw_start;
	while (y < draw_end)
	{
		my_pixel_put(data->img, x, y, color);
		y++;
	}
}

double	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000.0) + (time.tv_usec / 1000.0));
}

void	render_frame(t_data *data)
{
	t_texture_column	tc;
	int					wall_height;
	int					x;

	x = 0;
	ft_memset(data->img.addr, 0, HEIGHT * data->img.linelen);
	while (x < WIDTH)
	{
		camera_position(data->player, x);
		exact_position_in_cell(data->player);
		distance_to_next_tile(data->player);
		define_step_len(data->player);
		advance_to_next_grid(data->player, data->map->grid);
		perpendicular_wall_distance(data->player);
		contact_position(data->player, data->texture);
		wall_height = (int)(HEIGHT / data->player->perp_wall_dist);
		draw_textured_column(&tc, data, x, wall_height);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	render_loop(void *param)
{
	t_data			*data;
	static double	old_time = 0;
	double			time;
	double			frame_time;

	data = (t_data *)param;
	time = get_time_in_ms();
	frame_time = (time - old_time) / 1000.0;
	old_time = time;
	update_player(data->player, data->map->grid, frame_time);
	render_frame(data);
	return (0);
}
