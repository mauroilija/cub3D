/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:54:05 by abita             #+#    #+#             */
/*   Updated: 2026/04/27 20:50:04 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	input_validity(t_map *line, int argc, char **argv)
{
	char	*last_dot;
	// char 	*slash;
	// char 	*first_dot;

	if (argc < 2)
		return (print_error("Error\npass a map file: '.cub'.\n"), EXIT_FAILURE);
	if (argc > 2)
		return (print_error("Error\ntoo many arguments.\n"), EXIT_FAILURE);
	// slash = ft_strrchr(argv[1], '/');
	// first_dot = ft_strchr(&slash[1], '.');
	// if (!first_dot || ft_strcmp(first_dot, ".cub") == 0)
	// 	return (print_error("Error\nmap is hidden.\n"),
	// 		EXIT_FAILURE);
	last_dot = ft_strrchr(argv[1], '.');
	if (!last_dot || ft_strcmp(last_dot, ".cub") != 0)
		return (print_error("Error\nmap must have '.cub' extension.\n"),
			EXIT_FAILURE);
	if (parser(argv[1], line) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data				data;
	t_map				map;
	t_player			player;
	t_texture_column	column;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&map, sizeof(t_map));
	if (input_validity(&map, argc, argv) != EXIT_SUCCESS)
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
