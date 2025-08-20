/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:30:18 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/20 17:08:42 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	normalize_angle(float *angle)
{
	// More efficient modular arithmetic
	while (*angle < 0)
		*angle += 2.0f * M_PI;
	while (*angle >= 2.0f * M_PI)
		*angle -= 2.0f * M_PI;
}

float	get_distance(t_cub *cub)
{
	float dx = cub->dr->x - cub->x_p;
	float dy = cub->dr->y - cub->y_p;
	cub->dr->dist = sqrt(dx * dx + dy * dy);
	if (cub->dr->dist <= 0.0f)
		cub->dr->dist = 0.01f;
	return (cub->dr->dist);
}

void	set_window_name(t_cub *cub)
{
	static float	last_dir = -1.0f;
	char			*name;

	// Only update window name if direction changed significantly  
	if (fabs(cub->dir_p - last_dir) < 0.1f)
		return;
	
	if (cub->dir_p < 0)
		cub->dir_p += 2.0f * M_PI;
	if (cub->dir_p > 2.0f * M_PI)
		cub->dir_p -= 2.0f * M_PI;
		
	if (cub->dir_p >= 0 && cub->dir_p < M_PI / 2)
		name = "EAST";
	else if (cub->dir_p >= M_PI / 2 && cub->dir_p < M_PI)
		name = "SOUTH";
	else if (cub->dir_p >= M_PI && cub->dir_p < 3 * M_PI / 2)
		name = "WEST";
	else
		name = "NORTH";
		
	mlx_set_window_title(cub->mlx, name);
	last_dir = cub->dir_p;
}

int	load_textures(t_cub *cub)
{
	cub->textcol->t_no = mlx_load_png(cub->textcol->no);
	if (!cub->textcol->t_no)
		return (printf("Error\nNO\n"), 1);
	cub->textcol->t_so = mlx_load_png(cub->textcol->so);
	if (!cub->textcol->t_so)
		return (printf("Error\nSO\n"), 1);
	cub->textcol->t_we = mlx_load_png(cub->textcol->we);
	if (!cub->textcol->t_we)
		return (printf("Error\nWE\n"), 1);
	cub->textcol->t_ea = mlx_load_png(cub->textcol->ea);
	if (!cub->textcol->t_ea)
		return (printf("Error\nEA\n"), 1);
	return (0);
}
