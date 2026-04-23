/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:04:38 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/23 14:13:57 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_texture_paths(t_texture_data *td)
{
	if (!td->no)
	{
		free(td->no);
		td->no = NULL;
	}
	if (!td->so)
	{
		free(td->so);
		td->so = NULL;
	}
	if (!td->ea)
	{
		free(td->ea);
		td->ea = NULL;
	}
	if (!td->we)
	{
		free(td->we);
		td->we = NULL;
	}
}

int	load_textures(t_data *data)
{
	char	*path[4];
	int		i;

	if (!data->t_data->no || !data->t_data->so
			|| !data->t_data->we || !data->t_data->ea)
		return (EXIT_FAILURE);
	path[0] = data->t_data->no;
	path[1] = data->t_data->so;
	path[2] = data->t_data->ea;
	path[3] = data->t_data->we;
	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx, path[i],
				&data->texture[i].width, &data->texture[i].height);
		if (!data->texture[i].img)
		{
			printf("Error: failed to load texture: %s\n", path[i]);
			exit(1);
		}
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
				&data->texture[i].bpp, &data->texture[i].line_len,
				&data->texture[i].endian);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	pixel_from_texture(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;
	int		value;

	pixel = texture->addr + (tex_y * texture->line_len
			+ tex_x * (texture->bpp / 8));
	ft_memcpy(&value, pixel, sizeof(int));
	return (value);
}

static t_texture	*get_texture(t_data *data)
{
	t_player	*p;

	p = data->player;
	if (p->side == 0)
	{
		if (p->step_x > 0)
			return (&data->texture[2]);
		return (&data->texture[3]);
	}
	else
	{
		if (p->step_y > 0)
			return (&data->texture[1]);
		return (&data->texture[0]);
	}
}

static void	init_tex_column(t_data *data, int wall_height,
			t_texture_column *texture_c)
{
	texture_c->texture = get_texture(data);
	printf("HEIGHT is: %d\n", HEIGHT);
	printf("wall height after call is: %d\n", wall_height);
	texture_c->draw_start = (HEIGHT / 2) - wall_height;
	printf("texture_c draw start before if statement: %d\n", texture_c->draw_start);
	if (texture_c->draw_start < 0)
		texture_c->draw_start = 0;
	printf("texture_c draw start: %d\n", texture_c->draw_start);
	texture_c->draw_end = HEIGHT / 2 + wall_height;
	if (texture_c->draw_end >= HEIGHT)
		texture_c->draw_end = HEIGHT - 1;
	printf("texture_c draw end: %d\n", texture_c->draw_end);
	texture_c->texture_x = (int)(data->player->wall_x
			* texture_c->texture->width);
	if ((data->player->side == 0 && data->player->ray_dir_x > 0)
		|| (data->player->side == 1 && data->player->ray_dir_y < 0))
		texture_c->texture_x = texture_c->texture->width
			- texture_c->texture_x - 1;
	texture_c->step = (float)texture_c->texture->height / (wall_height * 2);
	texture_c->texture_position = (texture_c->draw_start
			- HEIGHT / 2 + wall_height) * texture_c->step;
	printf("texture->position is: %f\n", texture_c->texture_position);
}

void	draw_textured_column(t_texture_column *texture_c, t_data *data,
			int ray_col, int wall_height)
{
	int	tex_y;

	init_tex_column(data, wall_height, texture_c);
	while (texture_c->draw_start < texture_c->draw_end)
	{
		printf("texture_position is: %f\n", texture_c->texture_position);
		printf("texture_height is: %d\n", texture_c->texture->height);
		tex_y = (int)texture_c->texture_position % texture_c->texture->height;
		printf("tex_y is: %d\n", tex_y);
		if (tex_y < 0)
		{
			printf("tex_y is not valid\n");
			exit (1);
		}
		texture_c->texture_position += texture_c->step;
		my_pixel_put(data->img, ray_col, texture_c->draw_start,
			pixel_from_texture(texture_c->texture, texture_c->texture_x,
				tex_y));
		texture_c->draw_start++;
	}
}
