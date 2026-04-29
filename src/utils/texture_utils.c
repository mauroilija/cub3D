/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:31:46 by abita             #+#    #+#             */
/*   Updated: 2026/04/29 12:24:13 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static int	match_texture(char *line, int i, char *id, int *count)
{
	if (line[i] != id[0] || line[i + 1] != id[1])
		return (-1);
	if (line[i + 2] != ' ' && line[i + 2] != '\t')
		return (-1);
	if (*count > 0)
		return (print_error(DUPLICATE_TEXTURE), EXIT_FAILURE);
	(*count)++;
	return (EXIT_SUCCESS);
}

int	is_texture_line(char *line, t_map *map)
{
	int	i;
	int	ret;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	ret = match_texture(line, i, "NO", &map->no_count);
	if (ret == -1)
		ret = match_texture(line, i, "SO", &map->so_count);
	if (ret == -1)
		ret = match_texture(line, i, "EA", &map->ea_count);
	if (ret == -1)
		ret = match_texture(line, i, "WE", &map->we_count);
	if (ret == EXIT_SUCCESS)
		map->texture_flag = true;
	if (ret == -1)
		return (EXIT_FAILURE);
	return (ret);
}

int	check_hidden_path(const char *path)
{
	char	*slash;

	slash = ft_strrchr(path, '.');
	if (!slash || slash == &path[0] || *(--slash) == '/')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
