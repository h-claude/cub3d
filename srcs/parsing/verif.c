/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:37:41 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/20 13:45:16 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	get_dir(t_cub *cub)
{
	char	player;

	player = cub->map[(int)cub->y_p][(int)cub->x_p];
	if (player == 'W')
		return (M_PI);
	if (player == 'E')
		return (0);
	if (player == 'N')
		return (3 * M_PI / 2);
	if (player == 'S')
		return (M_PI / 2);
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
