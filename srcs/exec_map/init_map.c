/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:59:19 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/14 15:16:41 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static mlx_t		*mlx;
static mlx_image_t	*image;
static mlx_image_t	*r_image;

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
	//printf("Player at %f, %f\n", y, x);
	//printf("Player at %d, %d\n", y1, x1);
	//printf("Player at %d, %d\n", y2, x2);
	if (cub->map[y1][x1] == '1'/* || cub->map[y1][x2] == '1' || cub->map[y2][x1] == '1' || cub->map[y2][x2] == '1'*/)
		return (0);
	else
		return (1);
}

void	input(void *cub1)
{
	t_cub	*cub = (t_cub *)cub1;
	float	new_x;
	float	new_y;
	float	move_speed = 0.05;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		exit(0); // faut faire ca bien
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		new_x = cub->x_p + cos(cub->dir_p) * move_speed;
		new_y = cub->y_p + sin(cub->dir_p) * move_speed;
		if (player_can_reach(new_y, new_x, cub))
		{
			cub->x_p = new_x;
			cub->y_p = new_y;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		new_x = cub->x_p - cos(cub->dir_p) * move_speed;
		new_y = cub->y_p - sin(cub->dir_p) * move_speed;
		if (player_can_reach(new_y, new_x, cub))
		{
			cub->x_p = new_x;
			cub->y_p = new_y;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		new_x = cub->x_p + cos(cub->dir_p + M_PI / 2) * move_speed;
		new_y = cub->y_p + sin(cub->dir_p + M_PI / 2) * move_speed;
		if (player_can_reach(new_y, new_x, cub))
		{
			cub->x_p = new_x;
			cub->y_p = new_y;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		new_x = cub->x_p + cos(cub->dir_p - M_PI / 2) * move_speed;
		new_y = cub->y_p + sin(cub->dir_p - M_PI / 2) * move_speed;
		if (player_can_reach(new_y, new_x, cub))
		{
			cub->x_p = new_x;
			cub->y_p = new_y;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		cub->dir_p -= 0.05;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		cub->dir_p += 0.05;
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

float	get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

uint32_t color_dist(uint32_t color, float distance)
{
	uint8_t r = (color & 0xFF0000) >> 16;
	uint8_t g = (color & 0x00FF00) >> 8;
	uint8_t b = (color & 0x0000FF);

	if (distance < 1)  // On évite de diviser par 0 en utilisant un seuil proche de 0
        distance = 1;
	r = r / distance;
	g = g / distance;
	b = b / distance;
	return (r << 16 | g << 8 | b);
}

void	put_wall(float	distance, float angle, t_cub *cub)
{
	if (distance > 10)
		distance = 10;
	if (distance < 0.5)
		distance = 0.5;

	uint32_t	wall_color = 0x00BB00;
	wall_color = color_dist(wall_color, distance);
	float		wall_height = HEIGHT / distance;
	float		wall_top = (HEIGHT / 2) - wall_height / 2;
	float		wall_bottom = (HEIGHT / 2) + wall_height / 2;
	int			x = angle * WIDTH / FOV;
	int			y = 0;

	// printf("Distance: %f\n", distance);
	// printf("Wall height: %f\n", wall_height);
	// printf("Wall top: %f\n", wall_top);
	// printf("Wall bottom: %f\n", wall_bottom);
	// printf("Wall width: %f\n", wall_width);
	// printf("Color: %x\n", wall_color);
	// printf("X: %d\n", x);
	// printf("Y: %d\n", y);

	while (y < wall_top)
	{
		mlx_put_pixel(r_image, x, y, cub->textcol->f);
		y++;
	}
	y = wall_top;
	while (y < wall_bottom)
	{
		if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT && y > wall_top && y < wall_bottom)
			mlx_put_pixel(r_image, x, y, (wall_color << 8) + 0xFF);
		y++;
	}
	y = wall_bottom;
	while (y < HEIGHT)
	{
		mlx_put_pixel(r_image, x, y, cub->textcol->c);
		y++;
	}
	x++;
	y = wall_bottom;
}

void	put_rays(t_cub *cub)
{
	float	angle = 0;
	float	ray_angle = 0;
	float	ray_x = cub->x_p;
	float	ray_y = cub->y_p;
	float	ray_dir_x;
	float	ray_dir_y;

	while (angle < FOV)
	{
		ray_angle = cub->dir_p + (angle - (FOV / 2)) * (M_PI / 180);
		ray_dir_y = sin(ray_angle);
		ray_dir_x = cos(ray_angle);
		ray_x = cub->x_p;
		ray_y = cub->y_p;
		while (cub->map[(int)ray_y][(int)ray_x] != '1' && (get_distance(cub->x_p, cub->y_p, ray_x, ray_y)) < 10)
		{
			//mlx_put_pixel(image, (ray_x * SCALING_SIZE), (ray_y * SCALING_SIZE), 0x0000FFFF);
			ray_x += ray_dir_x * 0.01;
			ray_y += ray_dir_y * 0.01;
		}
		float	distance = get_distance(cub->x_p, cub->y_p, ray_x, ray_y);
		if (distance < 1)
			distance = 1;
		distance *= fabs(cos(ray_angle - cub->dir_p));
		put_wall(distance, angle, cub);
		angle += 0.03;
	}
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
				//print_cub(j, i, cub->textcol->f, SCALING_SIZE);
			if (cub->map[y][x] == 'x' || cub->map[y][x] == '0')
				//print_cub(j, i, cub->textcol->c, SCALING_SIZE);
			if (is_player(cub->map[y][x]))
			{
				cub->map[y][x] = '0';
				//print_cub(j, i, cub->textcol->c, SCALING_SIZE);
			}
			i = i + 24;
			x++;
		}
		x = 0;
		i = 0;
		j = j + 24;
		y++;
	}
	//print_cub(cub->y_p * 24, cub->x_p * 24, 0x00FF0000, 10);
	int x_f = 0;
	int y_f = 0;
	while (y_f < HEIGHT)
	{
		while (x_f < WIDTH)
		{
			mlx_put_pixel(r_image, x_f, y_f, 0x000000);
			x_f++;
		}
		x_f = 0;
		y_f++;
	}
	put_rays(cub);
}

int	load_textures(t_cub *cub)
{
	cub->textcol->t_no = mlx_load_png(cub->textcol->no);
	if (!cub->textcol->t_no)
		return (1);
	cub->textcol->t_so = mlx_load_png(cub->textcol->so);
	if (!cub->textcol->t_so)
		return (mlx_delete_texture(cub->textcol->t_no), 1);
	cub->textcol->t_we = mlx_load_png(cub->textcol->we);
	if (!cub->textcol->t_we)
		return (mlx_delete_texture(cub->textcol->t_no), \
			mlx_delete_texture(cub->textcol->t_so), 1);
	cub->textcol->t_ea = mlx_load_png(cub->textcol->ea);
	if (!cub->textcol->t_ea)
		return (mlx_delete_texture(cub->textcol->t_no), \
				mlx_delete_texture(cub->textcol->t_so), \
				mlx_delete_texture(cub->textcol->t_we), 1);
	return (0);
}

int	show_map(t_cub *cub)
{
	mlx = mlx_init(WIDTH, HEIGHT, "THIS IS CUB3D YEAAAAAAAAAAAAAAAAAH", false);
	printf("\ncolor %x\n", cub->textcol->f);
	printf("color %x\n", cub->textcol->c);
	r_image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, r_image, 0, 0);
	mlx_loop_hook(mlx, put_color, cub);
	mlx_loop_hook(mlx, input, cub);
	mlx_loop(mlx);
	return (1);
}
