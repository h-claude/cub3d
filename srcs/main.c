/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:07:42 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/07 18:08:15 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_data(t_cub *cub)
{
	int	i;

	i = 0;
	printf("cub->textcol->no = %s", cub->textcol->no);
	printf("cub->textcol->so = %s", cub->textcol->so);
	printf("cub->textcol->we = %s", cub->textcol->we);
	printf("cub->textcol->ea = %s", cub->textcol->ea);
	printf("cub->textcol->f = %d\n", cub->textcol->f);
	printf("cub->textcol->c = %d\n\n", cub->textcol->c);
	printf("cub->x_p = %f\n", cub->x_p);
	printf("cub->y_p = %f\n", cub->y_p);
	printf("MAP :\n");
	while (cub->map[i])
	{
		printf("%s", cub->map[i]);
		i++;
	}
}

int	init_cub(t_cub *cub)
{
	cub->fd = 0;
	cub->x_p = 0;
	cub->y_p = 0;
	cub->dir = 0;
	cub->map = NULL;
	cub->textcol->c = -1;
	cub->textcol->f = -1;
	cub->textcol->ea = NULL;
	cub->textcol->we = NULL;
	cub->textcol->no = NULL;
	cub->textcol->so = NULL;
	return (0);
}

int	start_parsing(t_cub *cub, char *file)
{
	if (init_cub(cub))
		return (1);
	if (check_file(file, cub))
		return (1);
	if (get_data(cub))
		return (1);
	return (0);
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
	if (check_map(cub))
		return (1);
	if (show_map(cub))
		return (1);
}
