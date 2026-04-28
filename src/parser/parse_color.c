/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:00:00 by abita             #+#    #+#             */
/*   Updated: 2026/04/28 11:44:25 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static int	get_id_type(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (F);
	if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (C);
	return (EXIT_FAILURE);
}

static int	checker(char **split, int *rgb)
{
	int		j;

	j = 0;
	while (j < 3)
	{
		if (!split[j] || !is_number(split[j]))
			return (EXIT_FAILURE);
		rgb[j] = ft_atoi(split[j]);
		if (rgb[j] < 0 || rgb[j] > 255)
			return (EXIT_FAILURE);
		j++;
	}
	if (split[3])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	comma(char *line, int i)
{
	int		comma;

	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		i++;
	}
	if (comma >= 3)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	get_color_range(char *line)
{
	int		i;
	int		color;
	int		rgb[3];
	char	**split;
	char	*trim;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	i += 1;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	trim = ft_strtrim(&line[i], "\n \t");
	if (!trim)
		return (EXIT_FAILURE);
	if (comma(line, i) == EXIT_FAILURE)
		return (free(trim), EXIT_FAILURE);
	split = ft_split(trim, ',');
	if (!split)
		return (free(trim), free_split(split), EXIT_FAILURE);
	if (checker(split, rgb) == EXIT_FAILURE)
		return (free(trim), free_split(split), EXIT_FAILURE);
	color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (free(trim), free_split(split), color);
}

int	parse_color(char *line, t_color_data *color_data)
{
	int	id;
	int	color;

	id = get_id_type(line);
	if (id == EXIT_FAILURE)
		return (EXIT_FAILURE);
	color = get_color_range(line);
	if (color == EXIT_FAILURE)
		return (print_error("Error\nno color\n"), EXIT_FAILURE);
	if (id == F)
		color_data->floor_color = color;
	if (id == C)
		color_data->ceiling_color = color;
	return (EXIT_SUCCESS);
}
