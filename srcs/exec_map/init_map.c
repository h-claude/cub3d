/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:59:19 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/06 14:43:18 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static mlx_t	*mlx;
static mlx_image_t	*image;

int	player_can_reach(int y, int x, t_cub *cub)
{
	if (cub->map[y][x] == '1')
		return (0);
	else
		return (1);
}

void	input(void *cub1)
{
	t_cub *cub = (t_cub *)cub1;

	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		if (player_can_reach(cub->y_p - 1, cub->x_p, cub))
		{
			cub->map[cub->y_p][cub->x_p] = '0';
			cub->y_p--;
			cub->map[cub->y_p][cub->x_p] = 'N';
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		if (player_can_reach(cub->y_p + 1, cub->x_p, cub))
		{
			cub->map[cub->y_p][cub->x_p] = '0';
			cub->y_p++;
			cub->map[cub->y_p][cub->x_p] = 'N';
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		if (player_can_reach(cub->y_p, cub->x_p - 1, cub))
		{
			cub->map[cub->y_p][cub->x_p] = '0';
			cub->x_p--;
			cub->map[cub->y_p][cub->x_p] = 'N';
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		if (player_can_reach(cub->y_p, cub->x_p + 1, cub))
		{
			cub->map[cub->y_p][cub->x_p] = '0';
			cub->x_p++;
			cub->map[cub->y_p][cub->x_p] = 'N';
		}
	}
}

void	print_cub(int y, int x, int32_t color)
{
	int	y1 = y + 24;
	int	x1 = x + 24;
	while (y1 != y)
	{
		while (x1 != x)
		{
			mlx_put_pixel(image, x, y, color);
			x++;
		}
		x = x - 24;
		y++;
	}
}

void	put_color(void *cub1)
{
	int x;
	int y;
	int	i = 0;
	int j =0;
	t_cub	*cub;

	x = 0, y = 0;
	cub = (t_cub *)cub1;
	while (cub->map[y])
	{
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == ' ')
			{
					
				// print_cub(i, j , 0);
			}
			if (cub->map[y][x] == '1')
				print_cub(j, i, cub->textcol->f);
			if (cub->map[y][x] == 'x' || cub->map[y][x] == '0')
				print_cub(j, i, cub->textcol->c);
			if (is_player(cub->map[y][x]))
				print_cub(j, i, 0xFCD917FF);
			i = i + 24;
			x++;
		}
		x = 0;
		i = 0;
		j = j + 24;
		y++;
	}
}

int	show_map(t_cub *cub)
{
	mlx = mlx_init(1400, 900, "", false);
	image = mlx_new_image(mlx, 1400, 900);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop_hook(mlx, put_color, cub);
	mlx_loop_hook(mlx, input, cub);
	mlx_loop(mlx);
	return (1);
}