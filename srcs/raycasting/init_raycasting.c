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
#include <stdlib.h>
#include <sys/resource.h>

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

static void	update_sys_stats(t_cub *cub, double wall_dt, double cpu_dt)
{
	cub->fps_stats->cpu_pct = (float)(cpu_dt / wall_dt * 100.0);
	update_ram_mb(cub);
}

static mlx_image_t	*hud_put_string(t_cub *cub, const char *text, int y)
{
	mlx_image_t	*img;

	img = mlx_put_string(cub->mlx, text, 10, y);
	if (!img)
		fprintf(stderr, "Warning: mlx_put_string failed for HUD line \"%s\"\n",
			text);
	return (img);
}

void	refresh_hud(t_cub *cub)
{
	char	buf[32];

	if (cub->hud->fps_img)
		mlx_delete_image(cub->mlx, cub->hud->fps_img);
	if (cub->hud->cpu_img)
		mlx_delete_image(cub->mlx, cub->hud->cpu_img);
	if (cub->hud->ram_img)
		mlx_delete_image(cub->mlx, cub->hud->ram_img);
	cub->hud->fps_img = NULL;
	cub->hud->cpu_img = NULL;
	cub->hud->ram_img = NULL;
	if (!cub->hud->visible)
		return ;
	snprintf(buf, sizeof(buf), "FPS: %.0f", cub->fps_stats->cur_fps);
	cub->hud->fps_img = hud_put_string(cub, buf, 10);
	snprintf(buf, sizeof(buf), "CPU: %.1f%%", cub->fps_stats->cpu_pct);
	cub->hud->cpu_img = hud_put_string(cub, buf, 35);
	snprintf(buf, sizeof(buf), "RAM: %.0fMB", cub->fps_stats->ram_mb);
	cub->hud->ram_img = hud_put_string(cub, buf, 60);
}

static bool	record_frame_time(t_fps_stats *s, float delta)
{
	float	*new_buf;

	if (s->count == s->capacity)
	{
		new_buf = realloc(s->frame_times, s->capacity * 2 * sizeof(float));
		if (!new_buf)
			return (false);
		s->frame_times = new_buf;
		s->capacity *= 2;
	}
	s->frame_times[s->count++] = delta;
	return (true);
}

void	fps_counter(t_cub *cub)
{
	static struct timespec	last_wall;
	static struct timespec	last_stat;
	static struct rusage	last_cpu;
	static int				initialized = 0;
	struct timespec			now;
	struct rusage			cpu_now;
	float					delta;
	double					stat_elapsed;
	double					cpu_delta;

	clock_gettime(CLOCK_MONOTONIC, &now);
	getrusage(RUSAGE_SELF, &cpu_now);
	if (!initialized)
	{
		last_wall = now;
		last_stat = now;
		last_cpu = cpu_now;
		initialized = 1;
		return ;
	}
	delta = (now.tv_sec - last_wall.tv_sec)
		+ (now.tv_nsec - last_wall.tv_nsec) * 1e-9f;
	last_wall = now;
	if (delta <= 0.0f)
		return ;
	record_frame_time(cub->fps_stats, delta);
	cub->fps_stats->cur_fps = 1.0f / delta;
	stat_elapsed = (now.tv_sec - last_stat.tv_sec)
		+ (now.tv_nsec - last_stat.tv_nsec) * 1e-9;
	if (stat_elapsed >= 1.0)
	{
		cpu_delta = (cpu_now.ru_utime.tv_sec - last_cpu.ru_utime.tv_sec)
			+ (cpu_now.ru_utime.tv_usec - last_cpu.ru_utime.tv_usec) * 1e-6
			+ (cpu_now.ru_stime.tv_sec - last_cpu.ru_stime.tv_sec)
			+ (cpu_now.ru_stime.tv_usec - last_cpu.ru_stime.tv_usec) * 1e-6;
		update_sys_stats(cub, stat_elapsed, cpu_delta);
		refresh_hud(cub);
		last_stat = now;
		last_cpu = cpu_now;
	}
	printf("\rFPS: %.0f  CPU: %.1f%%  RAM: %.0fMB  ",
		1.0f / delta, cub->fps_stats->cpu_pct, cub->fps_stats->ram_mb);
	fflush(stdout);
}

static int	cmp_float_asc(const void *a, const void *b)
{
	float	fa;
	float	fb;

	fa = *(const float *)a;
	fb = *(const float *)b;
	if (fa < fb)
		return (-1);
	if (fa > fb)
		return (1);
	return (0);
}

static float	compute_low1_fps(float *times, int count)
{
	int		low1_count;
	double	sum;
	int		i;

	low1_count = count / 100;
	if (low1_count == 0)
		low1_count = 1;
	sum = 0.0;
	i = count - low1_count;
	while (i < count)
		sum += times[i++];
	return ((float)low1_count / (float)sum);
}

static float	compute_stability(float *times, int count, double mean)
{
	double	variance;
	int		i;

	variance = 0.0;
	i = 0;
	while (i < count)
	{
		variance += (times[i] - mean) * (times[i] - mean);
		i++;
	}
	return ((float)(sqrt(variance / count) / mean * 100.0));
}

void	print_fps_summary(t_cub *cub)
{
	t_fps_stats	*s;
	double		total;
	float		avg_fps;
	float		max_fps;
	float		low1_fps;
	float		stab;
	char		*stab_label;
	int			i;

	s = cub->fps_stats;
	if (s->count < 2)
		return ;
	qsort(s->frame_times, s->count, sizeof(float), cmp_float_asc);
	total = 0.0;
	i = 0;
	while (i < s->count)
		total += s->frame_times[i++];
	avg_fps = s->count / (float)total;
	max_fps = 1.0f / s->frame_times[0];
	low1_fps = compute_low1_fps(s->frame_times, s->count);
	stab = compute_stability(s->frame_times, s->count, total / s->count);
	if (stab < 5.0f)
		stab_label = "Tres stable";
	else if (stab < 15.0f)
		stab_label = "Stable";
	else if (stab < 30.0f)
		stab_label = "Modere";
	else
		stab_label = "Instable";
	printf("\n\n=== Recapitulatif FPS (%d frames) ===\n", s->count);
	printf("FPS Moyen : %.1f\n", avg_fps);
	printf("1%% Low    : %.1f\n", low1_fps);
	printf("FPS Max   : %.1f\n", max_fps);
	printf("Stabilite : %.1f%% CV (%s)\n", stab, stab_label);
}

void	draw(void *cub1)
{
	t_cub	*cub;

	cub = (t_cub *)cub1;
	set_window_name(cub);
	put_rays(cub);
	fps_counter(cub);
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
