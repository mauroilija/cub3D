/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:04:38 by milija-h          #+#    #+#             */
/*   Updated: 2026/04/16 12:17:17 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// redo this all, completly wrong
void	texture_file(t_data *data, t_texture_data *texture, void **image)
{
	int		width;
	int		height;
	char	*img_adr;

	if (texture->no)
		image = mlx_xpm_file_to_image(data->mlx, texture->no, &width, &height);
	else if (texture->ea)
		image = mlx_xpm_file_to_image(data->mlx, texture->so, &width, &height);
	else if (texture->so)
		image = mlx_xpm_file_to_image(data->mlx, texture->ea, &width, &height);
	else
		image = mlx_xpm_file_to_image(data->mlx, texture->we, &width, &height);
	img_adr = mlx_get_data_addr(image, &data->img.bpp,
		&data->img.linelen, &data->img.endian);
}
