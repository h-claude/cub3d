/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:32:06 by hclaude           #+#    #+#             */
/*   Updated: 2025/01/30 15:15:52 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_wall(float angle, t_cub *cub)
{
	uint32_t	wall_color;
	int			x;
	int			y;
	int			x_width;

	x = angle * WIDTH / FOV;
	y = -1;
	x_width = x + 6;
	wall_color = 0;
	while (++y < HEIGHT)
	{
		if (y >= cub->dr->wall_top && y <= cub->dr->wall_bot)
			wall_color = color_dist(get_text_color(\
				cub, cub->dr->wall_height, y), cub->dr->dist);
		while (x <= x_width && x < WIDTH)
		{
			if (y < cub->dr->wall_top)
				mlx_put_pixel(cub->image, x++, y, cub->textcol->c);
			else if (y >= cub->dr->wall_top && y <= cub->dr->wall_bot)
				mlx_put_pixel(cub->image, x++, y, wall_color);
			else
				mlx_put_pixel(cub->image, x++, y, cub->textcol->f);
		}
		x = angle * WIDTH / FOV;
	}
}

void	put_wall(float angle, t_cub *cub)
{
	cub->dr->wall_height = HEIGHT / cub->dr->dist;
	cub->dr->wall_top = (HEIGHT / 2) - cub->dr->wall_height / 2;
	cub->dr->wall_bot = (HEIGHT / 2) + cub->dr->wall_height / 2;
	draw_wall(angle, cub);
}

void	launch_rays(t_cub *cub)
{
	size_t	length;

	length = ft_strlen(cub->map[(int)cub->dr->y]);
	while (!cub->hw && get_distance(cub) < 10)
	{
		cub->dr->x += cub->dr->dir_x * 0.01;
		if ((size_t)cub->dr->y < cub->map_len \
			&& (size_t)cub->dr->x < length \
			&& cub->map[(int)cub->dr->y][(int)cub->dr->x] == '1')
		{
			cub->we = true;
			cub->hw = true;
		}
		cub->dr->y += cub->dr->dir_y * 0.01;
		if (!cub->hw && (size_t)cub->dr->y < cub->map_len \
			&& (size_t)cub->dr->x < length \
			&& cub->map[(int)cub->dr->y][(int)cub->dr->x] == '1')
		{
			cub->we = false;
			cub->hw = true;
		}
	}
}

void	put_rays(t_cub *cub)
{
	float	ray;
	float	ray_angle;

	cub->dr->x = cub->x_p;
	cub->dr->y = cub->y_p;
	cub->hw = false;
	ray = 0;
	while (ray < FOV)
	{
		ray_angle = cub->dir_p + (ray - (FOV / 2)) * (M_PI / 180);
		cub->dr->dir_y = sin(ray_angle);
		cub->dr->dir_x = cos(ray_angle);
		cub->dr->x = cub->x_p;
		cub->dr->y = cub->y_p;
		cub->hw = false;
		launch_rays(cub);
		get_distance(cub);
		cub->dr->dist *= fabs(cos(ray_angle - cub->dir_p));
		put_wall(ray, cub);
		ray += 0.2;
	}
}
