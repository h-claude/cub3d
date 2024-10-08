/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:59:19 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/08 16:36:57 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static mlx_t		*mlx;
static mlx_image_t	*image;

int	player_can_reach(float y, float x, t_cub *cub)
{
	int	y1;
	int	x1;
	int	y2;
	int	x2;

	y1 = (int)(y * 24);
	x1 = (int)(x * 24);
	y2 = (int)((y + (float)10 / 24) * 24);
	x2 = (int)((x + (float)10 / 24) * 24);
	y1 = y1 / 24;
	x1 = x1 / 24;
	y2 = y2 / 24;
	x2 = x2 / 24;
	printf("Player at %f, %f\n", y, x);
	printf("Player at %d, %d\n", y1, x1);
	printf("Player at %d, %d\n", y2, x2);
	if (cub->map[y1][x1] == '1' || cub->map[y1][x2] == '1' || cub->map[y2][x1] == '1' || cub->map[y2][x2] == '1')
		return (0);
	else
		return (1);
}

void	input(void *cub1)
{
	t_cub	*cub = (t_cub *)cub1;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		exit(0); // faut faire ca bien
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		if (player_can_reach(cub->y_p - 0.05, cub->x_p, cub))
			cub->y_p -= 0.05;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		if (player_can_reach(cub->y_p + 0.05, cub->x_p, cub))
			cub->y_p += 0.05;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		if (player_can_reach(cub->y_p, cub->x_p - 0.05, cub))
			cub->x_p -= 0.05;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		if (player_can_reach(cub->y_p, cub->x_p + 0.05, cub))
			cub->x_p += 0.05;
	}
}

void	print_cub(int y, int x, int32_t color, int size)
{
	int	y1 = y + size;
	int	x1 = x + size;

	while (y1 != y)
	{
		while (x1 != x)
		{
			mlx_put_pixel(image, x, y, color);
			x++;
		}
		x = x - size;
		y++;
	}
}

void	print_player(t_cub *cub)
{
	float	i = 0;
	float	j = 0;

	i = cub->x_p * 24;
	j = cub->y_p * 24;
	while (j < cub->y_p * 24 + 10)
	{
		while (i < cub->x_p * 24 + 10)
		{
			mlx_put_pixel(image, i, j, 0x00FF0000);
			i++;
		}
		i = cub->x_p * 24;
		j++;
	}
}

void	put_rays(t_cub *cub)
{
	int		angle = 0;
	float	ray_angle = 0;
	float	ray_x = cub->x_p;
	float	ray_y = cub->y_p;
	float	ray_dir_x;
	float	ray_dir_y;

	while (angle < 360)
	{
		ray_angle = angle * (M_PI / 180);
		ray_dir_y = sin(ray_angle);
		ray_dir_x = cos(ray_angle);
		ray_x = cub->x_p;
		ray_y = cub->y_p;
		angle++;
		while (cub->map[(int)ray_y][(int)ray_x] != '1')
		{
			printf("Ray at %f, %f\n", ray_x * 24, ray_y * 24);
			mlx_put_pixel(image, ray_x * 24, ray_y * 24, 0x0000FF00);
			ray_x += ray_dir_x * 0.1;
			ray_y += ray_dir_y * 0.1;
		}
	}
	//float r_x = cub->x_p;

	//while (cub->map[(int)cub->y_p][(int)r_x] != '1')
	//{
	//	//printf("Ray at %f, %f\n", r_x * 24, cub->y_p * 24);
	//	//printf("Player at %f, %f\n", cub->x_p * 10, cub->y_p * 10);
	//	//print_cub((int)cub->y_p * 24, r * 24, 0x0000FF00, 10);
	//	mlx_put_pixel(image, r_x * 24, cub->y_p * 24, 0x0000FF00);
	//	r_x += 0.10;
	//}
	//float	r_y = cub->y_p;
	//while (cub->map[(int)r_y][(int)cub->x_p] != '1')
	//{
	//	//printf("Ray at %f, %f\n", cub->x_p * 24, r_y * 24);
	//	//printf("Player at %f, %f\n", cub->x_p * 10, cub->y_p * 10);
	//	//print_cub(r * 24, (int)cub->x_p * 24, 0x0000FF00, 10);
	//	mlx_put_pixel(image, cub->x_p * 24, r_y * 24, 0x0000FF00);
	//	r_y += 0.10;
	//}
}

void	put_color(void *cub1)
{
	int		x;
	int		y;
	int		i = 0;
	int		j = 0;
	t_cub	*cub;

	x = 0, y = 0;
	cub = (t_cub *)cub1;
	while (cub->map[y])
	{
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == ' ')
			{
			}
			if (cub->map[y][x] == '1')
				print_cub(j, i, cub->textcol->f, SCALING_SIZE);
			if (cub->map[y][x] == 'x' || cub->map[y][x] == '0')
				print_cub(j, i, cub->textcol->c, SCALING_SIZE);
			if (is_player(cub->map[y][x]))
			{
				cub->map[y][x] = '0';
				print_cub(j, i, cub->textcol->c, SCALING_SIZE);
			}
			i = i + 24;
			x++;
		}
		x = 0;
		i = 0;
		j = j + 24;
		y++;
	}
	print_player(cub);
	put_rays(cub);
}

int	show_map(t_cub *cub)
{
	mlx = mlx_init(1000, 1000, "", false);
	image = mlx_new_image(mlx, 1000, 1000);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop_hook(mlx, put_color, cub);
	mlx_loop_hook(mlx, input, cub);
	mlx_loop(mlx);
	return (1);
}
