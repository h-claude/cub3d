/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:47:24 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/19 04:36:28 by hclaude          ###   ########.fr       */
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
	struct s_textcol	*textcol; // textures and colors
	struct s_dr			*dr; // data ray
}	t_cub;

// parsing
int		start_parsing(t_cub *cub, char *file);
int32_t	convert_int(char *str);
int		data_is_collected(t_cub *cub);
int		verif_syntax(char *str);
size_t	tab_len(char **tab);
void	free_gnl(int fd);
int		get_data(t_cub *cub);
int		parse_map(t_cub *cub);
int		check_map(t_cub *cub);
int		flood_fill(char **map, int y, int x);
int		show_map(t_cub *cub);
int		is_player(char player);
int		check_file(char *file, t_cub *cub);
int		is_multiple_player(t_cub *cub);
int		is_wrong_character(char **map);
int		is_player(char player);

// utils
void	freetab(char **tab);
size_t	lstlen(t_list *lst);
void	free_lst(t_list **lst);

#endif