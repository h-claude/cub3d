/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:59:19 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/18 19:56:24 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static mlx_t		*mlx;
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
			mlx_put_pixel(r_image, x, y, color);
			x++;
		}
		x = x - size;
		y++;
	}
}

uint32_t color_dist(uint32_t color, float distance)
{
	uint8_t r = (color) >> 24;
	uint8_t g = (color) >> 16;
	uint8_t b = (color) >> 8;
	float n_distance;

	n_distance = distance / 2;
	if (n_distance < 1)
		n_distance = 1;
	r = r  /  (n_distance);
	g = g /  (n_distance);
	b = b / (n_distance);
	return (r << 24 | g << 16 | b << 8 | 255);
}

uint32_t	get_pixel(t_cub *cub, mlx_texture_t *texture, float height, int y)
{
	uint32_t	color;
	int 		x_text;
	int			y_text;
	double		care;
	int i;
	(void)height;

	if (cub->WE)
		x_text = (int)(modf(cub->dr->y, &care) * texture->width) % texture->width;
	else
		x_text = (int)(modf(cub->dr->x, &care) * texture->width) % texture->width;

	y_text = (int)((y / height) * (texture->height / cub->dr->distance)) % texture->height;

	i = (y_text * texture->width + x_text) * texture->bytes_per_pixel;
	color = texture->pixels[i] << 24 | texture->pixels[i + 1] << 16 | texture->pixels[i + 2] << 8 | 255;
	return (color);
}

uint32_t	get_text_color(t_cub *cub, float height, int y)
{
	mlx_texture_t	*text;
	uint32_t		text_color;

	text_color = 0xFFFFFFFF;
	text = NULL;
	if (cub->WE)
	{
		if (cub->dr->dir_x < 0.0)
			text = cub->textcol->t_we; // pour l'ouest
		else
			text = cub->textcol->t_ea; // pour l'est
	}
	else
	{
		if (cub->dr->dir_y < 0.0)
			text = cub->textcol->t_no; // pour le nord
		else
			text = cub->textcol->t_so; // pour le sud
	}
	if (cub->HIT_WALL)
		text_color = get_pixel(cub, text, height, y);
	return (text_color);
}

void	put_wall(float angle, t_cub *cub)
{
	uint32_t	wall_color;
	if (cub->dr->distance > 10)
		cub->dr->distance = 10;
	if (cub->dr->distance < 1)
		cub->dr->distance = 1;
	float		wall_height = HEIGHT / cub->dr->distance;
	float		wall_top = (HEIGHT / 2) - wall_height / 2;
	float		wall_bottom = (HEIGHT / 2) + wall_height / 2;
	int			x = angle * WIDTH / FOV;
	int			y = 0;
	int			x_width = x + 7;

	while (y < HEIGHT)
	{
		wall_color = color_dist(get_text_color(cub, wall_bottom - wall_top, y), cub->dr->distance);
		while (x <= x_width && x < WIDTH)
		{
			if (y < wall_top)
				mlx_put_pixel(r_image, x, y, cub->textcol->c);
			else if (y >= wall_top && y <= wall_bottom)
				mlx_put_pixel(r_image, x, y, wall_color);
			else if (y > wall_bottom)
				mlx_put_pixel(r_image, x, y, cub->textcol->f);
			x++;
		}
		x = angle * WIDTH / FOV;
		y++;

	}
}

void	normalize_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
}

float	get_distance(t_cub *cub)
{
	cub->dr->distance = sqrt(pow(cub->dr->x - cub->x_p, 2) + pow(cub->dr->y - cub->y_p, 2));
	return (cub->dr->distance);
}

float radiant = M_PI / 180;

void	put_rays(t_cub *cub)
{
	float	ray = 0;
	float	ray_angle = 0;

	cub->dr->x = cub->x_p;
	cub->dr->y = cub->y_p;
	cub->HIT_WALL = false;
	while (ray < FOV)
	{
		normalize_angle(&cub->dir_p);
		ray_angle = cub->dir_p + (ray - (FOV / 2)) * (M_PI / 180);
		cub->dr->dir_y = sin(ray_angle);
		cub->dr->dir_x = cos(ray_angle);
		cub->dr->x = cub->x_p;
		cub->dr->y = cub->y_p;
		cub->HIT_WALL = false;
		while (!cub->HIT_WALL && get_distance(cub) < 10)
		{
			cub->dr->x += cub->dr->dir_x * 0.01;
			if (cub->map[(int)cub->dr->y][(int)cub->dr->x] == '1')
			{
				cub->WE = true;
				cub->HIT_WALL = true;
			}
			cub->dr->y += cub->dr->dir_y * 0.01;
			if (!cub->HIT_WALL && cub->map[(int)cub->dr->y][(int)cub->dr->x] == '1')
			{
				cub->WE = false;
				cub->HIT_WALL = true;
			}
		}
		get_distance(cub);
		if (cub->dr->distance < 1)
			cub->dr->distance = 1;
		cub->dr->distance *= fabs(cos(ray_angle - cub->dir_p));
		put_wall(ray, cub);
		ray += 0.25;
	}
}

void	set_window_name(float dir_p)
{
	char	*name;

	if (dir_p < 0)
		dir_p += 2 * M_PI;
	if (dir_p > 2 * M_PI)
		dir_p -= 2 * M_PI;
	if (dir_p >= 0 && dir_p < M_PI / 2)
		name = "EAST";
	else if (dir_p >= M_PI / 2 && dir_p < M_PI)
		name = "SOUTH";
	else if (dir_p >= M_PI && dir_p < 3 * M_PI / 2)
		name = "WEST";
	else if (dir_p >= 3 * M_PI / 2 && dir_p < 2 * M_PI)
		name = "NORTH";
	mlx_set_window_title(mlx, name);
}

void	put_color(void *cub1)
{
	//int		x;
	//int		y;
	//int		i = 0;
	//int		j = 0;
	t_cub	*cub;

	//x = 0, y = 0;
	cub = (t_cub *)cub1;
	set_window_name(cub->dir_p);
	put_rays(cub);
	//while (cub->map[y])
	//{
	//	while (cub->map[y][x])
	//	{
	//		if (cub->map[y][x] == ' ')
	//		{
	//		}
	//		if (cub->map[y][x] == '1')
	//			print_cub(j, i, cub->textcol->f, SCALING_SIZE);
	//		if (cub->map[y][x] == 'x' || cub->map[y][x] == '0')
	//			print_cub(j, i, cub->textcol->c, SCALING_SIZE);
	//		if (is_player(cub->map[y][x]))
	//		{
	//			cub->map[y][x] = '0';
	//			print_cub(j, i, cub->textcol->c, SCALING_SIZE);
	//		}
	//		i = i + 24;
	//		x++;
	//	}
	//	x = 0;
	//	i = 0;
	//	j = j + 24;
	//	y++;
	//}
	//print_cub(cub->y_p * 24, cub->x_p * 24, 0x00FF0000, 10);
	//int x_f = 0;
	//int y_f = 0;
	//while (y_f < HEIGHT)
	//{
	//	while (x_f < WIDTH)
	//	{
	//		mlx_put_pixel(r_image, x_f, y_f, 0x000000);
	//		x_f++;
	//	}
	//	x_f = 0;
	//	y_f++;
	//}

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
				mlx_delete_texture(cub->textcol->t_we), printf("EA\n"),1);
	return (0);
}

int	show_map(t_cub *cub)
{
	if (load_textures(cub))
		return ((void)printf("ERROR\n"), 1);
	mlx = mlx_init(WIDTH, HEIGHT, "THIS IS CUB3D YEAAAAAAAAAAAAAAAAAH", false);
	r_image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, r_image, 0, 0);
	mlx_loop_hook(mlx, put_color, cub);
	mlx_loop_hook(mlx, input, cub);
	mlx_loop(mlx);
	return (1);
}
