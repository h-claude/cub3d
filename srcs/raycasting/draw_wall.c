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
	uint32_t	ceiling_color;
	uint32_t	floor_color;
	int			x;
	int			y;
	int			x_width;
	int			wall_start;
	int			wall_end;

	x = angle * WIDTH_DIV_FOV;
	x_width = x + COLUMN_WIDTH;
	
	// Pre-calculate colors once per column
	ceiling_color = cub->textcol->c;
	floor_color = cub->textcol->f;
	wall_start = (int)cub->dr->wall_top;
	wall_end = (int)cub->dr->wall_bot;
	
	// Clamp wall bounds
	if (wall_start < 0) wall_start = 0;
	if (wall_end >= HEIGHT) wall_end = HEIGHT - 1;
	
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < wall_start)
			wall_color = ceiling_color;
		else if (y > wall_end)
			wall_color = floor_color;
		else
			wall_color = color_dist(get_text_color(cub, cub->dr->wall_height, y), cub->dr->dist);
		
		// Draw the horizontal line for this y coordinate
		x = angle * WIDTH_DIV_FOV;
		while (x <= x_width && x < WIDTH)
		{
			mlx_put_pixel(cub->image, x, y, wall_color);
			x++;
		}
	}
}

void	put_wall(float angle, t_cub *cub)
{
	cub->dr->wall_height = HEIGHT / cub->dr->dist;
	cub->dr->wall_top = HEIGHT_DIV2 - cub->dr->wall_height * 0.5f;
	cub->dr->wall_bot = HEIGHT_DIV2 + cub->dr->wall_height * 0.5f;
	draw_wall(angle, cub);
}

void	launch_rays(t_cub *cub)
{
	float	max_dist_sq; // Use squared distance to avoid sqrt
	int		map_x, map_y;
	int		max_iterations;
	float	dx, dy;

	max_dist_sq = MAX_RAY_DISTANCE * MAX_RAY_DISTANCE;
	max_iterations = 500; // Prevent infinite loops
	
	while (!cub->hw && --max_iterations > 0)
	{
		cub->dr->x += cub->dr->dir_x * RAY_STEP_SIZE;
		cub->dr->y += cub->dr->dir_y * RAY_STEP_SIZE;
		
		// Check distance without sqrt
		dx = cub->dr->x - cub->x_p;
		dy = cub->dr->y - cub->y_p;
		if (dx * dx + dy * dy > max_dist_sq)
			break;
		
		map_x = (int)cub->dr->x;
		map_y = (int)cub->dr->y;
		
		// Bounds check with early exit
		if (map_y < 0 || (size_t)map_y >= cub->map_len || 
			map_x < 0 || (size_t)map_x >= ft_strlen(cub->map[map_y]))
			break;
			
		if (cub->map[map_y][map_x] == '1')
		{
			// Determine if we hit a vertical or horizontal wall
			if (fabs(cub->dr->x - (float)map_x - 0.5f) > fabs(cub->dr->y - (float)map_y - 0.5f))
				cub->we = false;
			else
				cub->we = true;
			cub->hw = true;
		}
	}
}

void	put_rays(t_cub *cub)
{
	float	ray;
	float	ray_angle;
	float	cos_cache, sin_cache;
	float	angle_correction;

	cub->dr->x = cub->x_p;
	cub->dr->y = cub->y_p;
	cub->hw = false;
	ray = 0;
	while (ray < FOV)
	{
		ray_angle = cub->dir_p + (ray - (FOV / 2)) * (M_PI / 180);
		cos_cache = cos(ray_angle);
		sin_cache = sin(ray_angle);
		
		cub->dr->dir_y = sin_cache;
		cub->dr->dir_x = cos_cache;
		cub->dr->x = cub->x_p;
		cub->dr->y = cub->y_p;
		cub->hw = false;
		launch_rays(cub);
		
		// Cache distance calculation
		cub->dr->dist = sqrt((cub->dr->x - cub->x_p) * (cub->dr->x - cub->x_p) + 
						   (cub->dr->y - cub->y_p) * (cub->dr->y - cub->y_p));
		if (cub->dr->dist <= 0)
			cub->dr->dist = 0.01;
		
		// Apply fisheye correction
		angle_correction = ray_angle - cub->dir_p;
		cub->dr->dist *= fabs(cos(angle_correction));
		put_wall(ray, cub);
		ray += RAY_INCREMENT;
	}
}
