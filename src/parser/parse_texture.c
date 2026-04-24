/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:56:47 by abita             #+#    #+#             */
/*   Updated: 2026/04/24 17:22:52 by milija-h         ###   ########.fr       */
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
	return (-1);
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

static int	pass_path(int id, char *path, t_texture_data *t_data)
{
	if (id == -1)
		return (EXIT_FAILURE);
	if (id == NO)
	    t_data->no = ft_strdup(path);
	if (id == SO)
		t_data->so = ft_strdup(path);
	if (id == WE)
		t_data->we = ft_strdup(path);
	if (id == EA)
		t_data->ea = ft_strdup(path);
	return (EXIT_SUCCESS);
}

int	parse_texture(char *line, t_texture_data *t_data)
{
	int		id;
	char	*path;
	char	*slash;
	int fd;

	id = get_id_type(line);
	path = get_path(line);
	if (!path)
		return (-1);
	slash = ft_strrchr(path, '/');
	if (slash && slash[1] == '.')
	{
		print_error("Error\nthis is a hidden path\n");
		return (free(path), EXIT_FAILURE);
	}
	fd = open (path, O_RDONLY);
	if (fd == -1)
		return (print_error("Error\nfile doesn't exist\n"), 
			free(path), EXIT_FAILURE);
	if (pass_path(id, path, t_data) == EXIT_FAILURE)
		return (free(path), EXIT_FAILURE);
	return (free(path), EXIT_SUCCESS);
}
