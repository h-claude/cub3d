/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:07:42 by hclaude           #+#    #+#             */
/*   Updated: 2024/09/30 19:16:35 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void print_data(t_cub *cub)
{
	printf("cub->textcol->no = %s", cub->textcol->no);
	printf("cub->textcol->so = %s", cub->textcol->so);
	printf("cub->textcol->we = %s", cub->textcol->we);
	printf("cub->textcol->ea = %s\n", cub->textcol->ea);
	int i = 0;
	printf("MAP :\n");
	while (cub->map[i])
	{
		printf("%s", cub->map[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_cub	*cub;
	
	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	cub = malloc(sizeof(t_cub));
	if (!cub)
	{
		printf("Error\nMalloc failed\n");
		return (1);
	}
	cub->textcol = malloc(sizeof(t_textcol));
	if (!cub->textcol)
	{
		printf("Error\nMalloc failed\n");
		return (1);
	}
	if (start_parsing(cub, argv[1]))
		return (1); // faire fonction qui free tout
	print_data(cub);
}
