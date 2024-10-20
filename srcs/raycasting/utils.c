/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:30:18 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/20 13:52:32 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	normalize_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
}

float	get_distance(t_cub *cub)
{
	cub->dr->dist = sqrt(pow(cub->dr->x - cub->x_p, 2) \
		+ pow(cub->dr->y - cub->y_p, 2));
	if (cub->dr->dist <= 0)
		cub->dr->dist += 0.01;
	return (cub->dr->dist);
}

void	set_window_name(t_cub *cub)
{
	char	*name;

	if (cub->dir_p < 0)
		cub->dir_p += 2 * M_PI;
	if (cub->dir_p > 2 * M_PI)
		cub->dir_p -= 2 * M_PI;
	if (cub->dir_p >= 0 && cub->dir_p < M_PI / 2)
		name = "EAST";
	else if (cub->dir_p >= M_PI / 2 && cub->dir_p < M_PI)
		name = "SOUTH";
	else if (cub->dir_p >= M_PI && cub->dir_p < 3 * M_PI / 2)
		name = "WEST";
	else if (cub->dir_p >= 3 * M_PI / 2 && cub->dir_p < 2 * M_PI)
		name = "NORTH";
	mlx_set_window_title(cub->mlx, name);
}

int	load_textures(t_cub *cub)
{
	cub->textcol->t_no = mlx_load_png(cub->textcol->no);
	if (!cub->textcol->t_no)
		return (printf("NO\n"), 1);
	cub->textcol->t_so = mlx_load_png(cub->textcol->so);
	if (!cub->textcol->t_so)
		return (mlx_delete_texture(cub->textcol->t_no), printf("SO\n"), 1);
	cub->textcol->t_we = mlx_load_png(cub->textcol->we);
	if (!cub->textcol->t_we)
		return (mlx_delete_texture(cub->textcol->t_no), \
			mlx_delete_texture(cub->textcol->t_so), printf("WE\n"), 1);
	cub->textcol->t_ea = mlx_load_png(cub->textcol->ea);
	if (!cub->textcol->t_ea)
		return (mlx_delete_texture(cub->textcol->t_no), \
				mlx_delete_texture(cub->textcol->t_so), \
				mlx_delete_texture(cub->textcol->t_we), printf("EA\n"), 1);
	return (0);
}
