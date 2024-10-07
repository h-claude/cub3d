/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:49:45 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/07 14:02:40 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	flood_fill(char **map, int y, int x)
{
	if (y < 0 || x < 0)
		return (0);
	if (!map[y] || !map[y][x] || map[y][x] == '\t' || map[y][x] == ' ')
		return (1);
	if (map[y][x] == 'x' || map[y][x] == '1')
		return (0);
	if (map[y][x] == '0')
		map[y][x] = 'x';
	if (flood_fill(map, y + 1, x))
		return (1);
	if (flood_fill(map, y, x + 1))
		return (1);
	if (flood_fill(map, y - 1, x))
		return (1);
	if (flood_fill(map, y, x - 1))
		return (1);
	return (0);
}
