/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 21:19:46 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/29 11:51:30 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub.h"

void	compute_speed(t_player *p, double frame_time)
{
	p->move_speed = frame_time * 5.0;
	p->rot_speed = frame_time * 3.0;
}

void	move_forward_backward(t_player *p, double move_speed, char **map,
			int dir)
{
	double	new_x;
	double	new_y;

	new_x = p->pos_x + p->dir_x * move_speed * dir;
	new_y = p->pos_y + p->dir_y * move_speed * dir;
	if (map[(int)p->pos_y][(int)new_x] != '1')
		p->pos_x = new_x;
	if (map[(int)new_y][(int)p->pos_x] != '1')
		p->pos_y = new_y;
}

void	rotate_player(t_player *p, double rot_speed, int dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	angle = rot_speed * dir;
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void	move_left_right(t_player *p, double move_speed, char **map, int dir)
{
	double	new_x;
	double	new_y;

	new_x = p->pos_x + p->dir_y * move_speed * dir;
	new_y = p->pos_y - p->dir_x * move_speed * dir;
	if (map[(int)p->pos_y][(int)new_x] != '1')
		p->pos_x = new_x;
	if (map[(int)new_y][(int)p->pos_x] != '1')
		p->pos_y = new_y;
}

void	update_player(t_player *p, char **map, double frame_time)
{
	compute_speed(p, frame_time);
	if (p->key_up)
		move_forward_backward(p, p->move_speed, map, 1);
	if (p->key_down)
		move_forward_backward(p, p->move_speed, map, -1);
	if (p->key_left)
		rotate_player(p, p->rot_speed, -1);
	if (p->key_right)
		rotate_player(p, p->rot_speed, +1);
	if (p->a_key)
		move_left_right(p, p->move_speed, map, 1);
	if (p->d_key)
		move_left_right(p, p->move_speed, map, -1);
}
