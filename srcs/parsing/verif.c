/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:37:41 by hclaude           #+#    #+#             */
/*   Updated: 2024/09/27 19:31:05 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

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
		printf("Error\n%s\n", strerror);
		return (1);
	}
	return (0);
}

int	start_parsing(t_cub *cub, char *file)
{
	if (check_file(file, cub))
		return (1);
	//parsing here
}