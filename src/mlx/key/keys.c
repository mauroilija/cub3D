/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:33:15 by abita             #+#    #+#             */
/*   Updated: 2026/04/29 15:20:35 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub.h"

int	keyhandler(int keycode, void *param)
{
	t_data		*data;

	data = (t_data *)param;
	if (keycode == 65362 || keycode == 119)
		data->player->key_up = true;
	if (keycode == 65364 || keycode == 115)
		data->player->key_down = true;
	if (keycode == 65361)
		data->player->key_left = true;
	if (keycode == 65363)
		data->player->key_right = true;
	if (keycode == 97)
		data->player->a_key = true;
	if (keycode == 100)
		data->player->d_key = true;
	if (keycode == 65307)
		ft_exit(data, 0);
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_data		*data;
	t_player	*p;

	data = (t_data *)param;
	p = data->player;
	if (keycode == 65362 || keycode == 119)
		p->key_up = false;
	if (keycode == 65364 || keycode == 115)
		p->key_down = false;
	if (keycode == 65361)
		p->key_left = false;
	if (keycode == 65363)
		p->key_right = false;
	if (keycode == 97)
		data->player->a_key = false;
	if (keycode == 100)
		data->player->d_key = false;
	return (0);
}
