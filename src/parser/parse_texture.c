/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:56:47 by abita             #+#    #+#             */
/*   Updated: 2026/04/28 20:35:10 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static int	get_id_type(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (NO);
	if (line[i] == 'S' && line[i + 1] == 'O')
		return (SO);
	if (line[i] == 'W' && line[i + 1] == 'E')
		return (WE);
	if (line[i] == 'E' && line[i + 1] == 'A')
		return (EA);
	return (EXIT_FAILURE);
}

static char	*get_path(char *line)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	i += 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	path = (char *)malloc((ft_strlen(line + i)) + 1 * sizeof(char));
	if (!path)
		return (NULL);
	ft_strlcpy(path, line + i, ft_strlen(line + i));
	return (path);
}

static int	pass_path(int id, char *path, t_texture_data *texture_data)
{
	if (id == 1)
		return (EXIT_FAILURE);
	if (id == NO)
		texture_data->no = ft_strdup(path);
	if (id == SO)
		texture_data->so = ft_strdup(path);
	if (id == WE)
		texture_data->we = ft_strdup(path);
	if (id == EA)
		texture_data->ea = ft_strdup(path);
	return (EXIT_SUCCESS);
}

int	parse_texture(char *line, t_texture_data *texture_data)
{
	int		id;
	char	*path;
	int		fd;
	char 	*path_trimmed;

	id = get_id_type(line);
	if (!id)
		return (EXIT_FAILURE);
	path = get_path(line);
	if (!path)
		return (EXIT_FAILURE);
	path_trimmed = ft_strtrim(path, "\n \t");
	if (!path)
		return (EXIT_FAILURE);
	if (check_hidden_path(path_trimmed) == EXIT_FAILURE)
		return (print_error(HIDDEN_PATH), free(path),
			free(path_trimmed), EXIT_FAILURE);
	fd = open(path_trimmed, O_RDONLY);
	if (fd == -1)
		return (print_error(CANT_OPEN_FILE), free(path),
			free(path_trimmed), EXIT_FAILURE);
	if (pass_path(id, path_trimmed, texture_data) == EXIT_FAILURE)
		return (free_texture_paths(texture_data), free(path),
			path = NULL, free(path_trimmed), EXIT_FAILURE);
	return (free(path), path = NULL, free(path_trimmed), EXIT_SUCCESS);
}
