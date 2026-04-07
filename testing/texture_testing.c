#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_txt_type
{
	NO,
	SO,
	WE,
	EA
}		t_txt_type;

typedef struct s_texture_data
{
	int	no;
	int	so;
	int	we;
	int	ea;
}		t_texture_data;

int	get_id_type(char *line)
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

char	*get_path(char *line)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	i += 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	path = (char *)malloc((strlen(line + i)) + 1 * sizeof(char));
	if (!path)
		return (NULL);
	strcpy(path, line + i);
	return (path);
}

int	main(void)
{
	int id;
	char *path;
	char *slash;
	char *dot;
	t_texture_data t_data;

	// texture type if it is NO, SO, WE, EA
	id = get_id_type("NO ./path_to_the_north_texture");
	// printf("the texture type: %i\n", id);
	// check if it is a path
	path = get_path("NO texture/.xpm");
	// printf("the path is: %s\n", path);

	slash = strrchr(path, '/');
	// printf("backslash: %s\n", slash);
	if (slash && slash[1] == '.')
	{
		printf("error: this is a hidden path\n");
		return (EXIT_FAILURE);
	}
	dot = strrchr(path, '.');
	// printf("dot: %s\n", dot);
	if (!dot || strcmp(dot, ".xpm") != 0)
		return (printf("error\n"), EXIT_FAILURE);

	int fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (id == NO)
		t_data.no = fd;
	if (id == SO)
		t_data.so = fd;
	if (id == WE)
		t_data.we = fd;
	if (id == EA)
		t_data.ea = fd;
	return (EXIT_SUCCESS);
}