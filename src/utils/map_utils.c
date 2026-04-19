/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:56:33 by abita             #+#    #+#             */
/*   Updated: 2026/04/19 13:36:10 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_valid_input(char line)
{
	return (line == SPACE || line == WALL || line == NORTH || line == SOUTH
		|| line == EAST || line == WEST || line == ' ' || line == '\t');
}
int	is_player(char line)
{
	return (line == NORTH || line == SOUTH || line == EAST || line == WEST);
}
int	is_valid(char line)
{
	return (line == 'N' || line == 'S' || line == 'E' || line == 'W' || 
		line == '1' || line == '0');
}
int	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (EXIT_FAILURE);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (EXIT_FAILURE);
	while (line[i] && line[i] != '\n')
	{
		if (!is_valid_input(line[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
char **creating_2d_map(char **old, char *line)
{
	int i;
	char **new;

	i = 0;
	while (old && old[i])
		i++;
	new = (char **)ft_calloc((i + 2), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i++] = ft_strdup(line);
	new[i] = NULL;
	free(old);
	return (new);
}
