/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:41:32 by abita             #+#    #+#             */
/*   Updated: 2026/02/20 22:46:36 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum e_txt_type
{
	F = 11,
	C = 22
} t_txt_type;

typedef struct s_color_data
{
	int floor_color;
	int ceiling_color;
} t_color_data;

#define RGB (rgb[0] << 16) | (rgb[1] << 8) | (rgb[2])


void	free_split(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	start;
	int	count;

	i = 0;
	start = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (start < i)
			count++;
	}
	return (count);
}

static char	*word_copy(char const *s, int start, int end)
{
	int		i;
	int		j;
	char	*word;

	word = (char *)malloc(((end - start) + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = start;
	j = 0;
	while (i < end)
	{
		word[j] = s[i];
		j++;
		i++;
	}
	word[j] = '\0';
	return (word);
}

static int	save_the_word(char **split, int j)
{
	if (!split[j])
	{
		while (j < 0)
		{
			j--;
			free(split[j]);
		}
		free(split);
		return (0);
	}
	return (1);
}

static void	check(char const *s, char c, int *i, int *start)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	*start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		start;
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (s[i])
	{
		check(s, c, &i, &start);
		if (start < i)
		{
			split[j] = word_copy(s, start, i);
			if (!save_the_word(split, j))
				return (NULL);
			j++;
		}
	}
	split[j] = NULL;
	return (split);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		length;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && strchr(set, s1[start]))
		start++;
	end = strlen(s1) - 1;
	while (end >= start && strchr(set, s1[end]))
		end--;
	length = end - start + 1;
	str = (char *)malloc((length + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

static int	is_number(char *n)
{
	int	i;

	if (!n || !n[0])
		return (0);
	i = 0;
	while (n[i] == ' ' || n[i] == '\t')
		i++;
	while (n[i])
	{
		if (!isdigit(n[i]))
			return (0);
		i++;
	}
	return (1);
}
int get_id_type(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'F')
		return (F);
	if (line[i] == 'C')
		return (C);
	return (-1);
}
// int get_color_range(char *line)
// {
// 	int i;
// 	int j;
// 	char **split;
// 	int	rgb[3];
// 	// int comma;

// 	i = 0;
// 	while(line[i] == ' ' || line[i] == '\t')
// 		i++;
// 	i += 1;
// 	while(line[i] == ' ' || line[i] == '\t')
// 		i++;
// 	// comma = 0;
// 	// while (line[i])
// 	// {
// 	// 	if (line[i] == ',')
// 	// 		comma++;
// 	// 	i++;
// 	// }
// 	// if (comma == 3)
// 	// 	return (-1);
// 	char *trim = ft_strtrim(&line[i], "\n \t");
// 	if (!trim)
// 		return (-1);
// 	split = ft_split(line + i, ',');
// 	if (!split)
// 		return (free_split(split), -1);
// 	j = 0;
// 	while (j < 3)
// 	{
// 		if (!split[j] || !is_number(split[j]))
// 			return (-1);
// 		rgb[j] = atoi(split[j]);
// 		if (rgb[j] < 0 || rgb[j] > 255)
// 			return (free_split(split), -1);
// 		j++;
// 	}
// 	if (split[3])
// 		return(free_split(split), -1);
// 	free_split(split);
// 	return (RGB); // pass the rgb bit shifting
// }

static int	get_color_range(char *line)
{
	int		i;
	int		j;
	char	**split;
	int		rgb[3];
	int		color;
	int comma;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	i += 1;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	char *trim = ft_strtrim(&line[i], "\n \t");
	if (!trim)
		return (-1);
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		i++;
	}
	if (comma == 3)
		return (-1);
	split = ft_split(trim, ',');
	if (!split)
		return (free(trim), free_split(split), -1);
	j = 0;
	while (j < 3)
	{
		if (!split[j] || !is_number(split[j]))
			return (free(trim), free_split(split), -1);
		rgb[j] = atoi(split[j]);
		if (rgb[j] < 0 || rgb[j] > 255)
			return (free(trim), free_split(split), -1);
		j++;
	}
	if (split[3])
		return (free(trim), free_split(split), -1);
	color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (free(trim), free_split(split), color); // passing the rgb bit shifting
}

int	main(void)
{
	int id;
	int color;
	t_color_data c_data;

	id = get_id_type("F 220, 100, 0");
	if (id == -1)
		return (-1); // error
	color = get_color_range("F 220, 100, 0,");
	if (color == -1)
		return (printf("error\n"), -1); // error
	// printf("ID: %d\n", id);
	// printf("COLOR: %d (hex: %#x)\n", color, color);
	if (id == F)
		c_data.floor_color = color;
	if (id == C)
		c_data.ceiling_color = color;
	return (0);
}