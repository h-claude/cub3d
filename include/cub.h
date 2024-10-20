/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:47:24 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/20 16:39:25 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H

# define CUB_H

# include "../turbo_libft/include/libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/errno.h>
# include "../MLX42/include/MLX42/MLX42.h"

# define SCALING_SIZE 24
# define FOV 60
# define WIDTH 1920
# define HEIGHT 1080
# define MOVE_SPEED 0.05

typedef enum e_data_type
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}	t_data_type;

typedef struct s_textcol
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	mlx_texture_t	*t_no;
	mlx_texture_t	*t_so;
	mlx_texture_t	*t_we;
	mlx_texture_t	*t_ea;
	int32_t			f;
	int32_t			c;
}	t_textcol;

typedef struct s_dr
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	dist;
	// wall data
	float	wall_height;
	float	wall_top;
	float	wall_bot;
}	t_dr;

typedef struct cub
{
	int					fd;
	float				x_p; // player position
	float				y_p; // player position
	float				dir_p; // player direction
	bool				we; // WALL_EAST_OR_WEST
	bool				hw; // HIT_WALL
	char				**map; // map
	size_t				map_len;
	struct s_textcol	*textcol; // textures and colors
	struct s_dr			*dr; // data ray
	mlx_t				*mlx;
	mlx_image_t			*image;
}	t_cub;

// parsing
int			start_parsing(t_cub *cub, char *file);
int32_t		convert_int(char *str);
int			data_is_collected(t_cub *cub);
int			verif_syntax(char *str);
size_t		tab_len(char **tab);
void		free_gnl(int fd);
int			get_data(t_cub *cub);
int			parse_map(t_cub *cub);
int			check_map(t_cub *cub);
int			flood_fill(char **map, int y, int x);
int			show_map(t_cub *cub);
int			is_player(char player);
int			check_file(char *file, t_cub *cub);
int			is_multiple_player(t_cub *cub);
int			is_wrong_character(char **map);
int			is_player(char player);

// raycasting
int			launch_raycasting(t_cub *cub);
void		set_window_name(t_cub *cub);
float		get_distance(t_cub *cub);
void		normalize_angle(float *angle);
int			load_textures(t_cub *cub);
void		put_rays(t_cub *cub);
void		input(void *cub1);
uint32_t	get_text_color(t_cub *cub, float height, int y);
uint32_t	color_dist(uint32_t color, float distance);

// utils
void		freetab(char **tab, size_t len, bool no_len);
size_t		lstlen(t_list *lst);
void		free_lst(t_list **lst);
void		free_structs(t_cub **cub);
int			is_number(char *str);

#endif