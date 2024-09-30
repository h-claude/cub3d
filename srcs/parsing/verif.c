/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:37:41 by hclaude           #+#    #+#             */
/*   Updated: 2024/09/30 18:32:45 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	init_cub(t_cub *cub)
{
	cub->fd = 0;
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
	if (ft_strlen(file) < 4 &&
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
	get_data(cub);
	return (0);
}
