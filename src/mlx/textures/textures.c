/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:04:38 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/20 17:03:34 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	load_textures(t_data *data)
{
	char	*path[4]; // 4 directions
	int		i;

	path[0] = data->t_data->no;
	path[1] = data->t_data->so;
	path[2] = data->t_data->ea;
	path[3] = data->t_data->we;
	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx, path[i],
			&data->texture[i].width, &data->texture[i].height);
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
			&data->texture[i].bpp, &data->texture[i].line_len, &data->texture[i].endian);
		i++;
	}
}

int	pixel_from_texture(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;
	int		value;

	pixel = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8));
	ft_memcpy(&value, pixel, sizeof(int));
	return (value);
}

t_texture	*get_texture(t_data *data)
{
	t_player    *p;

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

