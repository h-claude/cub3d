/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:08:46 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/23 16:08:52 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_textures(t_cub *cub)
{
	if (cub->textcol->no)
	{
		if (cub->textcol->t_no)
			mlx_delete_texture(cub->textcol->t_no);
		free(cub->textcol->no);
	}
	if (cub->textcol->so)
	{
		if (cub->textcol->t_so)
			mlx_delete_texture(cub->textcol->t_so);
		free(cub->textcol->so);
	}
	if (cub->textcol->we)
	{
		if (cub->textcol->t_we)
			mlx_delete_texture(cub->textcol->t_we);
		free(cub->textcol->we);
	}
	if (cub->textcol->ea)
	{
		if (cub->textcol->t_ea)
			mlx_delete_texture(cub->textcol->t_ea);
		free(cub->textcol->ea);
	}
	free(cub->textcol);
}

void	free_structs(t_cub **cub)
{
	free_textures(*cub);
	free((*cub)->dr);
	if ((*cub)->image)
		mlx_delete_image((*cub)->mlx, (*cub)->image);
	if ((*cub)->hud)
	{
		if ((*cub)->hud->fps_img)
			mlx_delete_image((*cub)->mlx, (*cub)->hud->fps_img);
		if ((*cub)->hud->cpu_img)
			mlx_delete_image((*cub)->mlx, (*cub)->hud->cpu_img);
		if ((*cub)->hud->ram_img)
			mlx_delete_image((*cub)->mlx, (*cub)->hud->ram_img);
		free((*cub)->hud);
	}
	if ((*cub)->mlx)
		mlx_terminate((*cub)->mlx);
	if ((*cub)->map)
		freetab((*cub)->map, (*cub)->map_len, false);
	if ((*cub)->fps_stats)
	{
		free((*cub)->fps_stats->frame_times);
		free((*cub)->fps_stats);
	}
	free(*cub);
}
