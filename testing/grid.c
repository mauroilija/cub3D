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
	// new[i++] = strdup(line);
    char *clean = strdup(line);
    clean[strcspn(clean, "\n")] = '\0';
    new[i++] = clean;
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
char **copy_grid(char **old, int height)
{
	char **new_copy;
    int i;

	new_copy = (char **)calloc((height + 1), sizeof(char *));
	if (!new_copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		new_copy[i] = strdup(old[i]);
		i++;
	}
	new_copy[height] = NULL;
	return (new_copy);
}
int flood_fill(char **grid, int y, int x, int height)
{
    // printf("here: flood_fill called with y = %d, x = %d\n", y, x);
    // printf("what:\n height - 1: '%d'\n && y: %d\n && x: %d\n && grid[%d]: %d\n", height - 1, y, x, y, ft_strlen(grid[y]));
    
    if (y < 0 || y >= height || x < 0 || x >= ft_strlen(grid[y]))
        return (1);
    // here i check if the map is open by checking for spaces around the '0' cells, if a space then i return;
    if (grid[y][x] == ' ' || grid[y][x] == '\0')
        return (1);
    if (grid[y][x] == '1' || grid[y][x] == '*') // then i have either encountered a wall or i have been at a cell before i just stop and return
        return (0);
    grid[y][x] = '*'; //.. this i just mark the position just visited to let me knw that i have been here before  
    if (flood_fill(grid, y, x + 1, height))
        return (1);;
    if (flood_fill(grid, y, x - 1, height)) 
        return (1);
    if (flood_fill(grid, y + 1, x, height))
        return (1);
    if (flood_fill(grid, y - 1, x, height))
        return (1);
    return (0);
}

int get_validation(char **grid, int height)
{
    int x;
    int y;
    int player_x = 0;
    int player_y = 0;
    char **grid_copy;

    y = 0;
    while (y < height)
    {
        x = 0;
        while (grid[y][x])
        {
            // printf("\ngrid[%d][%d] = %c\n", y, x, grid[y][x]);
            // printf("here: \nheight - 1: '%d'\n && y: %d\n && x: %d\n", height - 1, y, x);
            if (grid[y][x] == 'N' || grid[y][x] == 'S' || grid[y][x] == 'E' || grid[y][x] == 'W')
            {
                player_x = x;
                player_y = y; 
                // printf("player position: x = %d, y = %d\n", player_x, player_y);
            }
            // if (grid[y][x] == '0')
            // {
            //     if (x >= ft_strlen(grid[y - 1]) || x >= ft_strlen(grid[y + 1])) // for uneven rows
            //     {
            //         printf("ERROR: map doest have even\n");
            //         return (1);
            //     }
            //     if ((grid[y][x - 1] == ' ' || grid[y][x - 1] == '\0') ||
            //     (grid[y][x + 1] == ' ' || grid[y][x + 1] == '\0') ||
            //     (grid[y - 1][x] == ' ' || grid[y - 1][x] == '\0') ||
            //     (grid[y + 1][x] == ' ' || grid[y + 1][x] == '\0'))
            //     {
            //         printf("ERROR: map is not closed\n");
            //         return (1);
            //     }
            //     // if ((grid[y][x - 1] == '1') || (grid[y][x + 1] == '1') || 
            //     //     (grid[y - 1][x] == '1') || (grid[y + 1][x] == '1'))
            //     //     {
            //     //         printf("ERROR: map is not valid\n");
            //     //         return (1);
            //     //     }
                printf("cell [%d][%d] is valid\n", y, x);
            // }
            x++;
        }
        y++;
    }
    grid_copy = copy_grid(grid, height);
    grid_copy[player_y][player_x] = '0';
    if (flood_fill(grid_copy, player_y, player_x, height)){
        printf("ERROR: map is not closed\n");
        return (1);
    }
    else
    {
        printf("PASSED: map is valid and closed\n");
        return (0);
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