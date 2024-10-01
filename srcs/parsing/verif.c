/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:37:41 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/01 16:40:53 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	is_player(char player)
{
	if (player == 'N' || player == 'S' || player == 'E' || player == 'W')
		return (1);
	return (0);
}

int	is_wrong_character(char **map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] != ' ' && map[y][x] != '\t'
				&& map[y][x] != '0' && map[y][x] != '1'
					&& !is_player(map[y][x]) && map[y][x] != '\n')
				return (1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int	is_multiple_player(t_cub *cub)
{
	int	y;
	int	x;
	int	player;

	y = 0;
	x = 0;
	player = 0;
	while (cub->map[y])
	{
		while (cub->map[y][x])
		{
			if (is_player(cub->map[y][x]))
			{
				cub->y_p = y;
				cub->x_p = x;
				player++;
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (player != 1)
		return (1);
	return (0);
}

int	check_map(t_cub *cub)
{
	if (is_multiple_player(cub))
		return ((void)printf("Error\nThere is multiple or no player\n"), 1);
	if (is_wrong_character(cub->map))
		return ((void)printf("Error\nThere is a wrong character\n"), 1);
	if (flood_fill(cub->map, cub->y_p, cub->x_p))
		return ((void)printf("Error\nThere is a big hole in the map\n"), 1);
	return (0);
}

int	init_cub(t_cub *cub)
{
	cub->fd = 0;
	cub->x_p = 0;
	cub->y_p = 0;
	cub->map = NULL;
	cub->textcol->c = -1;
	cub->textcol->f = -1;
	cub->textcol->ea = NULL;
	cub->textcol->we = NULL;
	cub->textcol->no = NULL;
	cub->textcol->so = NULL;
	return (0);
}

int	check_file(char *file, t_cub *cub)
{
	if (ft_strlen(file) < 4 ||
		ft_strncmp(file + (ft_strlen(file) - 4), ".cub", 4) != 0)
	{
		printf("Error\nWrong file extension\n");
		return (1);
	}
	cub->fd = open(file, O_RDONLY);
	if (cub->fd == -1)
	{
		printf("Error\nFailed to open map: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}

int	start_parsing(t_cub *cub, char *file)
{
	if (init_cub(cub))
		return (1);
	if (check_file(file, cub))
		return (1);
	if (get_data(cub))
		return (1);
	return (0);
}
