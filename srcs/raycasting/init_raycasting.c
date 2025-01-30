/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:59:19 by hclaude           #+#    #+#             */
/*   Updated: 2025/01/30 15:24:45 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>
#include <time.h>

uint32_t	color_dist(uint32_t color, float distance)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	float	n_distance;

	r = (color) >> 24;
	g = (color) >> 16;
	b = (color) >> 8;
	n_distance = distance / 2;
	if (n_distance < 1)
		n_distance = 1;
	r = r / (n_distance);
	g = g / (n_distance);
	b = b / (n_distance);
	return (r << 24 | g << 16 | b << 8 | 255);
}

uint32_t	get_pixel(t_cub *cub, mlx_texture_t *text, float height, int y)
{
	uint32_t		color;
	uint64_t		x_text;
	uint64_t		y_text;
	double			useless;
	int				i;

	if (cub->we)
		x_text = (int)(modf(cub->dr->y, &useless) * text->width) % text->width;
	else
		x_text = (int)(modf(cub->dr->x, &useless) * text->width) % text->width;
	y_text = (int)((y - (HEIGHT / 2) + (height / 2)) * text->height / height);
	if (y_text < 0)
		y_text = 0;
	if (y_text >= text->height)
		y_text = text->height - 1;
	i = (y_text * text->width + x_text) * text->bytes_per_pixel;
	color = text->pixels[i] << 24 | text->pixels[i + 1] << 16 \
		| text->pixels[i + 2] << 8 | 255;
	return (color);
}

uint32_t	get_text_color(t_cub *cub, float height, int y)
{
	mlx_texture_t	*text;
	uint32_t		text_color;

	text_color = 0xFFFFFFFF;
	text = NULL;
	if (cub->we)
	{
		if (cub->dr->dir_x < 0.0)
			text = cub->textcol->t_we;
		else
			text = cub->textcol->t_ea;
	}
	else
	{
		if (cub->dr->dir_y < 0.0)
			text = cub->textcol->t_no;
		else
			text = cub->textcol->t_so;
	}
	if (cub->hw)
		text_color = get_pixel(cub, text, height, y);
	return (text_color);
}

void	fps_counter()
{
	static int		frame_count = 0;
	static time_t	start_time = 0;
	time_t			current_time;

	frame_count++;
	current_time = time(NULL);
	if (start_time == 0)
		start_time = current_time;
	if (current_time - start_time >= 1)
	{
		printf("\rFPS: %d", frame_count);
		fflush(stdout);
		frame_count = 0;
		start_time = current_time;
	}
}

void	draw(void *cub1)
{
	t_cub	*cub;

	cub = (t_cub *)cub1;
	set_window_name(cub);
	put_rays(cub);
	fps_counter();
	input(cub);
}

int	launch_raycasting(t_cub *cub)
{
	if (load_textures(cub))
		return (1);
	cub->mlx = mlx_init(WIDTH, HEIGHT, \
		"THIS IS CUB3D YEAAAAAAAAAAAAAAAAAH", false);
	if (!cub->mlx)
		return (1);
	cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image)
		return (1);
	if (mlx_image_to_window(cub->mlx, cub->image, 0, 0))
		return (1);
	mlx_key_hook(cub->mlx, key_press_hook, cub);
	mlx_loop_hook(cub->mlx, draw, cub);
	mlx_loop(cub->mlx);
	return (1);
}
