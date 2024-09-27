/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:07:42 by hclaude           #+#    #+#             */
/*   Updated: 2024/09/27 16:37:13 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;
	
	if (argc != 2)
	{
		perror("Error\nInvalid number of arguments");
		return (1);
	}
	cub = malloc(sizeof(t_cub));
	if (!cub)
	{
		perror("Error\nMalloc failed");
		return (1);
	}
	if (start_parsing(cub, argv[1]))
		return (1);
}
