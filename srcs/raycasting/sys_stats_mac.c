/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_stats_mac.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 22:37:46 by hclaude           #+#    #+#             */
/*   Updated: 2026/05/11 22:37:46 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <mach/mach.h>

void	update_ram_mb(t_cub *cub)
{
	struct mach_task_basic_info	info;
	mach_msg_type_number_t		count;

	count = MACH_TASK_BASIC_INFO_COUNT;
	if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO,
			(task_info_t)&info, &count) == KERN_SUCCESS)
		cub->fps_stats->ram_mb = info.resident_size / (1024.0f * 1024.0f);
}
