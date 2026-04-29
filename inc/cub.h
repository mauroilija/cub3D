/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:15:08 by abita             #+#    #+#             */
/*   Updated: 2026/04/29 12:32:50 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

// scaling
# define WIDTH		1000
# define HEIGHT		900
# define TILE_SIZE	30

// arrow keys
# define LEFT	65361
# define UP		65362
# define RIGHT	65363
# define DOWN	65364

// escape keys
# define ESC	65307

// map
# define WALL	'1'
# define SPACE	'0'
# define NORTH	'N'
# define SOUTH	'S'
# define EAST	'E'
# define WEST	'W'

// error messages colors
# define RED			"\033[31m"
# define GREEN			"\e[0;32m"
# define RESET_COLOR	"\033[0m"

// return messages
# define INVALID_LINE 				"Error\nInvalid line.\n"
# define PASS_TEXTURE_COLOR 		"Error\nMissing a texture or color.\n"
# define FAILED_INIT_WINDOW 		"Error\nFailed to initialize the window.\n"
# define NO_MAP_FILE 				"Error\nPass a map file with \
										an extension: '.cub'.\n"
# define TOO_MANY_ARGS 				"Error\nToo many arguments.\n"
# define HIDDEN_PATH 				"Error\nSeems like you passed \
										a hidden file.\n"
# define CUB_EXTENSION				"Error\nThe map must have '.cub' \
										extension.\n"
# define CANT_OPEN_FILE				"Error\nFailed to open the file.\n"
# define NO_MAP_FOUND				"Error\nNo map was found in the file.\n"
# define MISSING_COLOR				"Error\nThere is a missing color.\n"
# define MISSING_TEXTURE			"Error\nThere is a missing texture.\n"
# define INVALID_LINE_END			"Error\nInvalid line after the map.\n"
# define DUPLICATE_TEXTURE			"Error\nDuplicate texture.\n"
# define DUPLICATE_COLOR			"Error\nDuplicate color.\n"
# define NOT_VALID_TEX_Y			"Error\ntex_y is not valid.\n"
# define FAILED_TO_LOAD_TEXTURE 	"Error\nfailed to load texture\n"

/* ************************************************************************** */
/*                             ENUM Texture Types                             */
/* ************************************************************************** */
typedef enum e_txt_type
{
	NO = 3,
	SO = 4,
	WE = 5,
	EA = 6
}			t_txt_type;

/* ************************************************************************** */
/*                             ENUM Color Types                               */
/* ************************************************************************** */
typedef enum e_color_type
{
	F = 11,
	C = 12
}			t_color_type;

/* ************************************************************************** */
/*                                   PLAYER                                   */
/* ************************************************************************** */
typedef struct s_player
{
	float		pos_x; //position in the world space
	float		pos_y;
	float		m_pos_x; // updated position in the world space
	float		m_pos_y;
	float		dir_x; //direction vectoor (where the player looks)
	float		dir_y;
	float		plane_x; //camera plane (perpendicular to FOV)
	float		plane_y;
	float		camera_x; //raycasting per column
	float		ray_dir_x;
	float		ray_dir_y;
	int			map_x; // current map tile
	int			map_y;
	int			step_x; //dda step direction
	int			step_y;
	float		delta_dist_x; //distance between grid crossings
	float		delta_dist_y;
	float		side_dist_x; //distance to next grid crossing
	float		side_dist_y;
	float		perp_wall_dist;
	float		wall_x; //exact coordinate where the ray hits the wall
	int			side; // wal info (1 = wall in x-axis, 0 = wall in y-axis)
	double		move_speed;
	double		rot_speed;
	float		new_dir_x;
	float		new_dir_y;
	int			texture_y;
	int			texture_x;
	bool		key_up;
	bool		key_down;
	bool		key_right;
	bool		key_left;
	bool		a_key;
	bool		d_key;
}				t_player;

/* ************************************************************************** */
/*                                   MLX Struct                               */
/* ************************************************************************** */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		linelen;
	int		bpp;
	int		endian;
}			t_img;

/* ************************************************************************** */
/*                                   Texture Struct	                          */
/* ************************************************************************** */
typedef struct s_texture_data
{
	char	*no; //stores path to texture path of the given direction
	char	*so;
	char	*we;
	char	*ea;
	char	*fd;
}			t_texture_data;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
	t_player	*texture_data;
}				t_texture;

/* ************************************************************************** */
/*                                   Color Struct                             */
/* ************************************************************************** */
typedef struct s_color_data
{
	int		floor_color;
	int		ceiling_color;
}			t_color_data;

/* ************************************************************************** */
/*                                  Map data                     		      */
/* ************************************************************************** */
typedef struct s_map
{
	char			*line;
	char			**grid;
	char			*path;
	int				height;
	int				player_count;
	bool			texture_flag;
	bool			color_flag;
	bool			map_flag;
	int				floor_count;
	int				ceiling_count;
	int				no_count;
	int				so_count;
	int				ea_count;
	int				we_count;
	t_color_data	color_data;
	t_texture_data	texture_data;	
}					t_map;

/* ************************************************************************** */
/*                               Texture drawing						      */
/* ************************************************************************** */
typedef struct s_texture_column
{
	int			draw_start;
	int			draw_end;
	int			texture_x;
	float		step;
	float		texture_position;
	t_texture	*texture;
}				t_texture_column;

/* ************************************************************************** */
/*                               	Mlx data                    		      */
/* ************************************************************************** */

typedef struct s_data
{
	t_img				img;
	void				*mlx;
	void				*win;
	int					i;
	t_map				*map;
	t_player			*player;
	t_texture_column	*text_column;
	t_texture			texture[4]; //each represents one direction texture
}					t_data;

/* ************************************************************************** */
/*                                   MLX Window                               */
/* ************************************************************************** */

int		init_window_and_display(t_data *data);
void	my_pixel_put(t_img img, int x, int y, int color);
void	mlx_loop_helper(t_data *data);
int		keyhandler(int keycode, void *param);
int		key_release(int keycode, void *param);
int		ft_exit(t_data *data, int exit_flag);

/* ************************************************************************** */
/*                                  Graphics                                  */
/* ************************************************************************** */
void	init_player(t_player *player, t_map *map);
void	define_step_len(t_player *player);
void	define_step_len(t_player *player);
void	camera_position(t_player *player, int x);
void	exact_position_in_cell(t_player *player);
void	distance_to_next_tile(t_player *player);
void	advance_to_next_grid(t_player *player, char **map);
void	perpendicular_wall_distance(t_player *player);
void	contact_position(t_player *player, t_texture *texture);
void	texture_column(t_player *player, int tex_width);
void	render_frame(t_data *data);
int		render_loop(void *param);
void	update_player(t_player *p, char **map, double frame_time);
void	compute_speed(t_player *p, double frame_time);
double	get_time_in_ms(void);
int		load_textures(t_data *data);
void	draw_textured_column(t_data *data, int ray_col, int wall_height);
void	draw_floor_ceiling(t_data *data, t_player *player, int x);

/* ************************************************************************** */
/*                                  Parser                                    */
/* ************************************************************************** */

int		validate_input(t_map *line, int argc, char **argv);
int		grid_validation(char **grid, int height, t_map *map);
int		map_parsing(char *line, t_map *map);
int		parse_texture(char *line, t_texture_data *t_data);
int		parse_color(char *line, t_color_data *color_data);
void	free_texture_paths(t_texture_data *td);

/* ************************************************************************** */
/*                                  Utils                                     */
/* ************************************************************************** */

void	init_line(t_map *map);
int		skip_whitespace(char *line);
int		is_texture_line(char *line, t_map *map);
int		is_color_line(char *line, t_map *map);
void	free_split(char **split);
void	print_error(const char *msg);
int		is_number(char *n);
int		check_hidden_path(const char *path);
char	**creating_2d_map(char **old, char *line);
int		is_map_line(char *line);
int		is_valid(char line);
int		is_player(char type);
int		is_valid_input(char line);
void	free_all(t_map *map);

#endif
