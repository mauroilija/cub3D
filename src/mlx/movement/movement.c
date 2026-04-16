/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 21:19:46 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/16 13:17:35 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//our game works on a frame per second (image rendered per second) basis, so
//S = V*t, 


void	move_player(t_player *player)
{
	int	speed;

	speed = 5;
	if (player->key_up)
		player->pos_y -= speed;
	if (player->key_down)
		player->pos_y += speed;
	if (player->key_left)
		player->pos_x -= speed;
	if (player->key_right)
		player->pos_x += speed;
}
