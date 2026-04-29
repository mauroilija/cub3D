/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:56:59 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/29 12:07:50 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub.h"

void	free_texture_paths(t_texture_data *td)
{
	if (td->no)
	{
		free(td->no);
		td->no = NULL;
	}
	if (td->so)
	{
		free(td->so);
		td->so = NULL;
	}
	if (td->ea)
	{
		free(td->ea);
		td->ea = NULL;
	}
	if (td->we)
	{
		free(td->we);
		td->we = NULL;
	}
}

int	load_textures(t_data *data)
{
	char	*path[4];
	int		i;

	path[0] = data->map->texture_data.no;
	path[1] = data->map->texture_data.so;
	path[2] = data->map->texture_data.ea;
	path[3] = data->map->texture_data.we;
	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx, path[i],
				&data->texture[i].width, &data->texture[i].height);
		if (!data->texture[i].img)
		{
			print_error(FAILED_TO_LOAD_TEXTURE);
			free_texture_paths(&data->map->texture_data);
			return (EXIT_FAILURE);
		}
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
				&data->texture[i].bpp, &data->texture[i].line_len,
				&data->texture[i].endian);
		i++;
	}
	free_texture_paths(&data->map->texture_data);
	return (EXIT_SUCCESS);
}
