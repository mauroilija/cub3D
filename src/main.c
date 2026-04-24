/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:54:05 by abita             #+#    #+#             */
/*   Updated: 2026/04/24 16:39:25 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int	input_validity(t_map *line, t_data *data, int argc, char **argv)
{
	char			*dot;

	if (argc < 2)
	{
		print_error("Error\npass a map file: '.cub'.\n");
		ft_exit_error(data);
	}
	if (argc > 2)
	{
		print_error("Error\ntoo many arguments.\n");
		ft_exit_error(data);
	}
	dot = ft_strrchr(argv[1], '.');
	if (!dot || ft_strcmp(dot, ".cub") != 0)
		return (print_error("Error\nmap must have '.cub' extension.\n"), 
			EXIT_FAILURE);
	if (parser(argv[1], line) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_map			map;
	t_player		player;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&map, sizeof(t_map));
	if (input_validity(&map, &data, argc, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	data.map = &map;
	init_window_and_display(&data);
	init_player(&player, &map);
	data.player = &player;
	mlx_loop_helper(&data);
	return (EXIT_SUCCESS);
}
