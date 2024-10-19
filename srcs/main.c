/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:07:42 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/19 19:08:59 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_data(t_cub *cub)
{
	int	i;

	i = 0;
	printf("cub->textcol->no = %s\n", cub->textcol->no);
	printf("cub->textcol->so = %s\n", cub->textcol->so);
	printf("cub->textcol->we = %s\n", cub->textcol->we);
	printf("cub->textcol->ea = %s\n", cub->textcol->ea);
	printf("cub->textcol->f = %d\n", cub->textcol->f);
	printf("cub->textcol->c = %d\n\n", cub->textcol->c);
	printf("cub->x_p = %f\n", cub->x_p);
	printf("cub->y_p = %f\n", cub->y_p);
	printf("cub->dir_p = %f\n\n", cub->dir_p);
	printf("MAP :\n");
	while (cub->map[i])
	{
		printf("%s", cub->map[i]);
		i++;
	}
}

void	init_structs(t_cub *cub)
{
	cub->fd = 0;
	cub->x_p = 0;
	cub->y_p = 0;
	cub->dir_p = 0;
	cub->map = NULL;
	cub->textcol->c = -1;
	cub->textcol->f = -1;
	cub->textcol->ea = NULL;
	cub->textcol->we = NULL;
	cub->textcol->no = NULL;
	cub->textcol->so = NULL;
	cub->textcol->t_ea = NULL;
	cub->textcol->t_we = NULL;
	cub->textcol->t_no = NULL;
	cub->textcol->t_so = NULL;
	cub->map_len = 0;
	cub->dr->x = 0;
	cub->dr->y = 0;
	cub->dr->dir_x = 0;
	cub->dr->dir_y = 0;
	cub->dr->dist = 0;
	cub->mlx = NULL;
	cub->image = NULL;
}

t_cub	*alloc_structs(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
	{
		printf("Error\nMalloc failed\n");
		return (NULL);
	}
	cub->textcol = malloc(sizeof(t_textcol));
	if (!cub->textcol)
	{
		printf("Error\nMalloc failed\n");
		return (free(cub), NULL);
	}
	cub->dr = malloc(sizeof(t_dr));
	if (!cub->dr)
	{
		printf("Error\nMalloc failed\n");
		return (free(cub->textcol), free(cub), NULL);
	}
	init_structs(cub);
	return (cub);
}

int	start_parsing(t_cub *cub, char *file)
{
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
	cub = alloc_structs();
	if (!cub)
		return (1);
	if (start_parsing(cub, argv[1]))
		return (free_structs(&cub), 1);
	if (check_map(cub))
		return (free_structs(&cub), 1);
	print_data(cub);
	if (show_map(cub))
		return (free_structs(&cub), 1);
	free_structs(&cub);
}
