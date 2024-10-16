/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:59:19 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/16 18:19:03 by hclaude          ###   ########.fr       */
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

uint32_t color_dist(uint32_t color, float distance)
{
	uint8_t r = (color & 0xFF0000) >> 16;
	uint8_t g = (color & 0x00FF00) >> 8;
	uint8_t b = (color & 0x0000FF);

	r = r / distance;
	g = g / distance;
	b = b / distance;
	return (r << 16 | g << 8 | b);
}

uint32_t	get_text_color(t_cub *cub, float y, float x, float wall_x)
{
	mlx_texture_t	*text;
	int				text_x;
	int				text_y;
	uint32_t		text_color;

	text_color = 0x8080800;
	text = NULL;
	if (cub->WE)
	{
		if (x < 0.0)
			text = cub->textcol->t_we; // pour l'ouest
		else
			text = cub->textcol->t_ea; // pour l'est
	}
	else
	{
		if (y < 0.0)
			text = cub->textcol->t_no; // pour le nord
		else
			text = cub->textcol->t_so; // pour le sud
	}
	text_x = (int)(wall_x * text->width) % text->width;
	text_y = (int)(y - (int)y) * text->height % text->height;
	if (cub->HIT_WALL)
		text_color = *(uint32_t *)(text->pixels + (text_y * text->width + text_x) * text->bytes_per_pixel);
	return (text_color);
}

void	put_wall(float	distance, float angle, float ray_x, float ray_y, t_cub *cub)
{
	uint32_t	wall_color;
	if (distance > 10)
		distance = 10;
	if (distance < 1)
		distance = 1;
	float		wall_height = HEIGHT / distance;
	float		wall_top = (HEIGHT / 2) - wall_height / 2;
	float		wall_bottom = (HEIGHT / 2) + wall_height / 2;
	int			x = angle * WIDTH / FOV;
	int			y = 0;
	int			x_width = x + 10;

	wall_color = get_text_color(cub, ray_y, ray_x, x);
	while (y < HEIGHT)
	{
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

float	normalize_angle(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

float	get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	put_rays(t_cub *cub)
{
	float	angle = 0;
	float	ray_angle = 0;
	float	ray_x = cub->x_p;
	float	ray_y = cub->y_p;
	float	ray_dir_x;
	float	ray_dir_y;
	float	distance;

	cub->HIT_WALL = false;
	while (angle < FOV)
	{
		cub->dir_p = normalize_angle(cub->dir_p);
		ray_angle = cub->dir_p + (angle - (FOV / 2)) * (M_PI / 180);
		ray_dir_y = sin(ray_angle);
		ray_dir_x = cos(ray_angle);
		ray_x = cub->x_p;
		ray_y = cub->y_p;
		cub->HIT_WALL = false;
		while (!cub->HIT_WALL && get_distance(cub->x_p, cub->y_p, ray_x, ray_y) < 10)
		{
			ray_x += ray_dir_x * 0.01;
			if (cub->map[(int)ray_y][(int)ray_x] == '1')
			{
				cub->WE = true;
				cub->HIT_WALL = true;
			}
			ray_y += ray_dir_y * 0.01;
			if (!cub->HIT_WALL && cub->map[(int)ray_y][(int)ray_x] == '1')
			{
				cub->WE = false;
				cub->HIT_WALL = true;
			}
		}
		distance = get_distance(cub->x_p, cub->y_p, ray_x, ray_y);
		if (distance < 1)
			distance = 1;
		distance *= fabs(cos(ray_angle - cub->dir_p));
		put_wall(distance, angle, ray_dir_x, ray_dir_y, cub);
		angle += 0.17;
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
	put_rays(cub);
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
	printf("NO Width: %d ", cub->textcol->t_no->width);
	printf("NO Height: %d\n", cub->textcol->t_no->height);
	printf("SO Width: %d ", cub->textcol->t_so->width);
	printf("SO Height: %d\n", cub->textcol->t_so->height);
	printf("WE Width: %d ", cub->textcol->t_we->width);
	printf("WE Height: %d\n", cub->textcol->t_we->height);
	printf("EA Width: %d ", cub->textcol->t_ea->width);
	printf("EA Height: %d\n", cub->textcol->t_ea->height);

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
