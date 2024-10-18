/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:57:38 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/19 00:58:49 by hclaude          ###   ########.fr       */
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
