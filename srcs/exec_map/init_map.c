/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:59:19 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/04 13:08:31 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_color(void *image)
{
	int i;
	int y;

	i = 0, y = 0;
	image = (mlx_image_t *)image;
	while (y < 100)
	{
		while (i < 100)
		{
			mlx_put_pixel(image, y, i, 6618880);
			i++;
		}
		i = 0;
		y++;
	}
}

int	show_map(t_cub *cub)
{
	mlx_t	*mlx;
	mlx_image_t	*image;

	(void)cub;
	mlx = mlx_init(1400, 900, "test", false);
	image = mlx_new_image(mlx, 1400, 900);
	mlx_image_to_window(mlx, image, 0, 0);
	int i, y;
	i = 0, y = 0;
	while (y < 100)
	{
		while (i < 100)
		{
			mlx_put_pixel(image, y, i, 6618880 % 255);
			i++;
		}
		i = 0;
		y++;
	}
	// mlx_loop_hook(mlx, put_color, image);
	mlx_loop(mlx);
	return (1);
}