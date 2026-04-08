# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <string.h>
# include <fcntl.h>

# define BUFFER_SIZE 40962

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);

char **map_add_line(char **old, char *line)
{
	int i;
	char **new;

	i = 0;
	while (old && old[i])
		i++;
	new = (char **)calloc((i + 2), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i++] = strdup(line);
	new[i] = NULL;
	free(old);
	return (new);
}
int ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int get_validation(char **grid, int height)
{
    int x;
    int y;
    float x_pos = 0.0;
    float y_pos = 0.0;

    y = 0;
    while (y < height)
    {
        x = 0;
        while (grid[y][x])
        {
            //  printf("grid[%d][%d] = %c\n", y, x, grid[y][x]);
             if (grid[y][x] == 'N' || grid[y][x] == 'S' || grid[y][x] == 'E' || grid[y][x] == 'W')
             {
                x_pos = x + 0.5;
                y_pos = y + 0.5; 
                printf("player position: x = %f, y = %f\n", x_pos, y_pos);
             }
            if (grid[y][x] == '0')
            {
                if ((grid[y][x - 1] == ' ' || grid[y][x - 1] == '\0') ||
                    (grid[y][x + 1] == ' ' || grid[y][x + 1] == '\0') ||
                    (grid[y - 1][x] == ' ' || grid[y - 1][x] == '\0') ||
                    (grid[y + 1][x] == ' ' || grid[y + 1][x] == '\0'))
                    {
                        printf("ERROR: map is not closed\n");
                        return (1);
                    }
                if (x >= ft_strlen(grid[y - 1]) || x >= ft_strlen(grid[y + 1])) // for uneven rows
                {
                    printf("ERROR: map doest have even\n");
                    return (1);
                }
                if ()
                printf("cell [%d][%d] is valid\n", y, x);
            }
            x++;
        }
        y++;
    }
    return (0);
}
int main()
{
    int fd = open("map.cub", O_RDONLY);
    if (fd == -1)
    {        printf("error\n");
        return (1);
    }
    char **grid = NULL;
    char *line;
    int height = 0;
    while ((line = get_next_line(fd)))
    {
    
        grid = map_add_line(grid, line);
        height++;
        free (line);
    }
    get_validation(grid, height);
    return (0);
}


/////////////////////
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