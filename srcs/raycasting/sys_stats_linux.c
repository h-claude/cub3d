/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_stats_linux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 22:37:46 by hclaude           #+#    #+#             */
/*   Updated: 2026/05/11 22:37:46 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	update_ram_mb(t_cub *cub)
{
	FILE	*fp;
	char	line[256];
	long	kb;

	fp = fopen("/proc/self/status", "r");
	if (!fp)
		return ;
	while (fgets(line, sizeof(line), fp))
	{
		if (strncmp(line, "VmRSS:", 6) == 0)
		{
			kb = atol(line + 6);
			cub->fps_stats->ram_mb = (float)kb / 1024.0f;
			break ;
		}
	}
	fclose(fp);
}
