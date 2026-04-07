/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:00:28 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/07 18:00:29 by milija-h         ###   ########.fr       */
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
