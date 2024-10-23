/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mouse_rotate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:38:02 by aurban            #+#    #+#             */
/*   Updated: 2024/10/23 13:43:33 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/**
 * @brief
 * Saves the initial mouses position
 * Each frame checks how much we moved from the initial position
 * Reset the mouse position back to the initial position each frame
*/
void	input_mouse_rotation(t_cub *cub, bool allow_mouse)
{
	static bool		local_allow_mouse = false;
	static int32_t	og_mouse_pos[2] = {0};
	int32_t			xy[2];

	if (local_allow_mouse != allow_mouse)
	{
		local_allow_mouse = allow_mouse;
		if (local_allow_mouse)
		{
			mlx_get_mouse_pos(cub->mlx, &og_mouse_pos[0], &og_mouse_pos[1]);
			mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_DISABLED);
		}
		else
			mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_NORMAL);
		return ;
	}
	if (!local_allow_mouse)
		return ;
	mlx_get_mouse_pos(cub->mlx, &xy[0], &xy[1]);
	cub->dir_p += MOUSE_SENSITIVITY * (xy[0] - og_mouse_pos[0]);
	mlx_set_mouse_pos(cub->mlx, og_mouse_pos[0], og_mouse_pos[1]);
}

/**
 * 1: set to true
 * 0: set to false
 * else: do nothing
 */
bool	rotation_mouse_sate(int b)
{
	static int	allow_mouse = false;

	if (b == 1)
		allow_mouse = true;
	else if (b == 0)
		allow_mouse = false;
	return (allow_mouse);
}

void	key_press_hook(mlx_key_data_t key_data, void *cub_ptr)
{
	t_cub		*cub;
	static bool	held = false;

	cub = (t_cub *)cub_ptr;
	if (key_data.key == MLX_KEY_SPACE)
	{
		if (!held)
			rotation_mouse_sate(!rotation_mouse_sate(-1));
		if (mlx_is_key_down(cub->mlx, MLX_KEY_SPACE))
			held = true;
		else
			held = false;
	}
}
