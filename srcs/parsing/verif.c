/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:37:41 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/08 14:56:38 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
				cub->y_p = (float)y;
				cub->x_p = (float)x;
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

float	get_dir(t_cub *cub)
{
	char	player;

	player = cub->map[(int)cub->y_p][(int)cub->x_p];
	if (player == 'N')
		return (M_PI / 2);
	if (player == 'S')
		return (3 * M_PI / 2);
	if (player == 'E')
		return (0);
	if (player == 'W')
		return (M_PI);
	return (-1);
}

int	check_map(t_cub *cub)
{
	if (is_multiple_player(cub))
		return ((void)printf("Error\nThere is multiple or no player\n"), 1);
	if (is_wrong_character(cub->map))
		return ((void)printf("Error\nThere is a wrong character\n"), 1);
	if (flood_fill(cub->map, cub->y_p, cub->x_p))
		return ((void)printf("Error\nThere is a big hole in the map\n"), 1);
	cub->dir_p = get_dir(cub);
	return (0);
}

int	check_file(char *file, t_cub *cub)
{
	if (ft_strlen(file) < 4
		|| ft_strncmp(file + (ft_strlen(file) - 4), ".cub", 4) != 0)
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
