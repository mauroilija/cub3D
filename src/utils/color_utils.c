/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:31:29 by abita             #+#    #+#             */
/*   Updated: 2026/04/29 12:22:32 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static int	match_color(char *line, int i, char *id, int *count)
{
	if (line[i] != id[0])
		return (-1);
	if (line[i + 1] != ' ' && line[i + 1] != '\t')
		return (-1);
	if (*count > 0)
		return (print_error(DUPLICATE_COLOR), EXIT_FAILURE);
	(*count)++;
	return (EXIT_SUCCESS);
}

int	is_color_line(char *line, t_map *map)
{
	int	i;
	int	ret;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	ret = match_color(line, i, "F", &map->floor_count);
	if (ret == -1)
		ret = match_color(line, i, "C", &map->ceiling_count);
	if (ret == EXIT_SUCCESS)
		map->color_flag = true;
	if (ret == -1)
		return (EXIT_FAILURE);
	return (ret);
}
