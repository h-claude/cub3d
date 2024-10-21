/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:27:56 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/21 16:12:01 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	player_can_reach(float y, float x, t_cub *cub)
{
	int	y1;
	int	x1;

	y1 = (int)(y * 24);
	x1 = (int)(x * 24);
	y1 = y1 / 24;
	x1 = x1 / 24;
	if (y1 < 0 || x1 < 0 || (size_t)y1 > cub->map_len \
		|| !cub->map[y1] || ft_strlen(cub->map[y1]) < (size_t)x1)
		return (0);
	if (cub->map[y1][x1] == '1')
		return (0);
	else
		return (1);
}

void	input_strafe(t_cub *cub)
{
	float	new_x;
	float	new_y;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		new_x = cub->x_p + cos(cub->dir_p + M_PI / 2) * MOVE_SPEED;
		new_y = cub->y_p + sin(cub->dir_p + M_PI / 2) * MOVE_SPEED;
		if (player_can_reach(new_y, new_x, cub))
		{
			cub->x_p = new_x;
			cub->y_p = new_y;
		}
	}
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		new_x = cub->x_p + cos(cub->dir_p - M_PI / 2) * MOVE_SPEED;
		new_y = cub->y_p + sin(cub->dir_p - M_PI / 2) * MOVE_SPEED;
		if (player_can_reach(new_y, new_x, cub))
		{
			cub->x_p = new_x;
			cub->y_p = new_y;
		}
	}
}

void	input_move(t_cub *cub)
{
	float	new_x;
	float	new_y;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		new_x = cub->x_p + cos(cub->dir_p) * MOVE_SPEED;
		new_y = cub->y_p + sin(cub->dir_p) * MOVE_SPEED;
		if (player_can_reach(new_y, new_x, cub))
		{
			cub->x_p = new_x;
			cub->y_p = new_y;
		}
	}
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		new_x = cub->x_p - cos(cub->dir_p) * MOVE_SPEED;
		new_y = cub->y_p - sin(cub->dir_p) * MOVE_SPEED;
		if (player_can_reach(new_y, new_x, cub))
		{
			cub->x_p = new_x;
			cub->y_p = new_y;
		}
	}
}

void	input(void *cub1)
{
	t_cub	*cub;

	cub = (t_cub *)cub1;
	input_move(cub);
	input_strafe(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->dir_p -= 0.05;
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->dir_p += 0.05;
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
		free_structs(&cub);
		exit(0);
	}
}
