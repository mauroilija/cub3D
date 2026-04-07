/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:00:28 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/07 20:48:40 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_player(t_player *player)
{
	//for the actual initial postion, maybe implement the function that takes
	// postion from the parsing
	player->x_position = WIDTH / 2;
	player->y_position = HEIGHT / 2;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->key_up = false;
}

void	draw_player(t_data *data, t_player *player)
{
	player->x_position = 1;
	player->y_position = 2;

	my_pixel_put(data->img, player->x_position, player->y_position, RED);
}

// int	main(int argc, char **argv)
// {
// 	t_data	data;
// 	t_player player;
// 	t_line	line;

// 	ft_bzero(&data, sizeof(t_data));
// 	ft_bzero(&line, sizeof(t_line));
// 	if (input_validity(&line, &data, argc, argv) != EXIT_SUCCESS)
// 		return (EXIT_FAILURE);
// 	init_window_and_display(&data);
// 	draw_player(&data,&player);
// 	mlx_loop_helper(&data);
// 	return (EXIT_SUCCESS);
// }
