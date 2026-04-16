/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:33:15 by abita             #+#    #+#             */
/*   Updated: 2026/04/16 22:28:40 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	keyhandler(int keycode, void *param)
{
	t_data		*data;
	t_player	*p;

	data = (t_data *)param;
	p = data->player;

	printf("KEY PRESSED: %d\n", keycode);
	if (keycode == 13)
		p->key_up = true;
	if (keycode == 1)
		p->key_down = true;
	if (keycode == 123)
		p->key_left = true;
	if (keycode == 124)
		p->key_right = true;
	if (keycode == 53)
		exit(0);
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_data		*data;
	t_player	*p;

	data = (t_data *)param;
	p = data->player;
	if (keycode == 13)
		p->key_up = false;
	if (keycode == 1)
		p->key_down = false;
	if (keycode == 123)
		p->key_left = false;
	if (keycode == 124)
		p->key_right = false;
	return (0);
}
