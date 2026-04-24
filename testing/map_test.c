# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <string.h>

# define BUFFER_SIZE 40962

typedef struct s_line
{
	char	*first_map_line;
	char	*last_map_line;
	int		is_first_line;
	int		error;
	char	*tmp;
	int		player_count;
	int		map_started;
}			t_line;

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

int init_parse_map(char **mat, t_map *line)
{
	line->first_map_line = NULL;
	line->last_map_line = NULL;
	line->is_first_line = 1;
	line->error = 0;
	line->player_count = 0;
	line->map_started = 0;
	return (0);
}
int main(void)
{
	char *line;
	char **mat;
	int fd;
	t_line	line;

	bzero(&line, sizeof(t_line));
	fd = open("map.cub", O_RDONLY);
	if (fd == -1)
		return(printf("error\n"), 1);

	while ((line = get_next_line(fd)))
	{
		mat = ft_split(line, '\n');
		if (mat)
		{
			parse_map(mat, &line);
			for(int i = 0; mat[i]; i++)
			{
				printf("[%s]\n", mat[i]);
				free(mat[i]);
			}
			free(mat);
		}
		else
			return (free(mat), 1);
		// printf("%s", line);
		free(line);
	}
}
////////////////////////////////////////////////////////////////////
static char	*line_to_return(char *leftovers)
{
	char	*print_line;
	size_t	i;
	size_t	j;
	size_t	remaining;

	i = 0;
	if (!leftovers)
		return (NULL);
	while (leftovers[i] && leftovers[i] != '\n')
		i++;
	if (leftovers[i] == '\n')
		i++;
	remaining = strlen(leftovers) - i;
	print_line = (char *)calloc(remaining + 1, sizeof(char));
	if (!print_line)
		return (free(leftovers), NULL);
	j = 0;
	while (leftovers[i])
		print_line[j++] = leftovers[i++];
	print_line[j] = '\0';
	free (leftovers);
	return (print_line);
}

static char	*copy_next_line(char *leftovers)
{
	size_t	i;
	char	*copied_line;

	i = 0;
	if (!leftovers)
		return (NULL);
	while (leftovers[i] && leftovers[i] != '\n')
		i++;
	copied_line = (char *)calloc(i + 2, sizeof(char));
	if (!copied_line)
		return (NULL);
	i = 0;
	while (leftovers[i] && leftovers[i] != '\n')
	{
		copied_line[i] = leftovers[i];
		i++;
	}
	if (leftovers[i] == '\n')
		copied_line[i++] = '\n';
	copied_line[i] = '\0';
	return (copied_line);
}

static char	*helper_for_gnl(char *leftovers, int fd, char *buffer)
{
	ssize_t		bytes_to_read;
	char		*temp;

	bytes_to_read = 1;
	while (bytes_to_read > 0)
	{
		if (leftovers != NULL)
		{
			if (strchr(leftovers, '\n') != NULL)
				break ;
		}
		bytes_to_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_to_read == -1)
			return (free(buffer), free (leftovers), NULL);
		buffer[bytes_to_read] = '\0';
		if (leftovers == NULL)
			temp = strdup(buffer);
		else
			temp = ft_strjoin (leftovers, buffer);
		free(leftovers);
		leftovers = temp;
		if (leftovers == NULL)
			break ;
	}
	return (free(buffer), leftovers);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*next_line;
	static char	*leftovers;

	if (fd == -1)
		return (free(leftovers), leftovers = NULL, NULL);
	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (free (leftovers), leftovers = NULL, NULL);
	leftovers = helper_for_gnl(leftovers, fd, buffer);
	if (!leftovers || leftovers[0] == '\0')
		return (free(leftovers), leftovers = NULL, NULL);
	next_line = copy_next_line(leftovers);
	if (next_line == NULL)
		return (free(leftovers), leftovers = NULL, NULL);
	leftovers = line_to_return(leftovers);
	if (leftovers == NULL)
		return (free(next_line), NULL);
	return (next_line);
}

//////////////////////////////////////////////////////////////////////


static void	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*new_str;

	s1_len = strlen(s1);
	s2_len = strlen(s2);
	new_str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, s1);
	ft_strcpy(new_str + s1_len, s2);
	return (new_str);
}
///////////////////////////////////////////////////////////////////////////////

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

static void	check(char const *s, char c, int *i, int *start)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	*start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
}
void	free_split1(char **split)
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
			if (!split[j])
				return (free_split1(split), NULL);
			j++;
		}
	}
	return (split[j] = NULL, split);
}