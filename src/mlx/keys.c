/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:33:15 by abita             #+#    #+#             */
/*   Updated: 2026/04/15 21:34:46 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	keyhandler(int key, t_data *data, t_player *player)
{
	if (key == ESC)
		ft_exit(data);
	if (key == UP)
		player->key_up = true;
	if (key == DOWN)
		player->key_down = true;
	if (key == LEFT)
		player->key_left = true;
	if (key == RIGHT)
		player->key_right = true;
	return (0);
}

int	key_release(int key, t_player *player)
{
	if (key == UP)
		player->key_up = false;
	if (key == DOWN)
		player->key_down = false;
	if (key == LEFT)
		player->key_left = false;
	if (key == RIGHT)
		player->key_right = false;
	return (0);
}
