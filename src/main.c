/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:54:05 by abita             #+#    #+#             */
/*   Updated: 2026/04/28 11:37:48 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	main(int argc, char **argv)
{
	t_data				data;
	t_map				map;
	t_player			player;
	t_texture_column	column;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&map, sizeof(t_map));
	if (validate_input(&map, argc, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	data.map = &map;
	if (init_window_and_display(&data) == EXIT_FAILURE)
		return (ft_exit(&data, 1),
			print_error("Error\nfailed initializing the window\n"),
			EXIT_FAILURE);
	init_player(&player, &map);
	data.player = &player;
	data.text_column = &column;
	mlx_loop_helper(&data);
	return (EXIT_SUCCESS);
}
