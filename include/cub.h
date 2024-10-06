/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:47:24 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/06 14:08:21 by hclaude          ###   ########.fr       */
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
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int32_t	f;
	int32_t	c;
}	t_textcol;

typedef struct cub
{
	int					fd;
	int				x_p;
	int				y_p;
	char				**map;
	struct s_textcol 	*textcol;
}	t_cub;

int	start_parsing(t_cub *cub, char *file);
int	get_data(t_cub *cub);
int	parse_map(t_cub *cub);
int	check_map(t_cub *cub);
int	flood_fill(char **map, int y, int x);
int	show_map(t_cub *cub);
int	is_player(char player);

#endif