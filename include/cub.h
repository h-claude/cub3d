/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:47:24 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/01 00:20:09 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H

# define CUB_H

# include "../turbo_libft/include/libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/errno.h>

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
	char				**map;
	struct s_textcol 	*textcol;
}	t_cub;

int	start_parsing(t_cub *cub, char *file);
int	get_data(t_cub *cub);
int	parse_map(t_cub *cub);
int	check_map(char **map);

#endif