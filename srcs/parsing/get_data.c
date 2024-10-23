/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:22:15 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/23 16:09:54 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_dup_data(t_cub *cub, t_data_type type)
{
	if (type == NORTH && cub->textcol->no)
		return ((void)printf("Error\nWhat is wrong with u?\n"), 1);
	if (type == SOUTH && cub->textcol->so)
		return ((void)printf("Error\nWhat is wrong with u?\n"), 1);
	if (type == WEST && cub->textcol->we)
		return ((void)printf("Error\nWhat is wrong with u?\n"), 1);
	if (type == EAST && cub->textcol->ea)
		return ((void)printf("Error\nWhat is wrong with u?\n"), 1);
	if (type == FLOOR && cub->textcol->f != -1)
		return ((void)printf("Error\nWhat is wrong with u?\n"), 1);
	if (type == CEILING && cub->textcol->c != -1)
		return ((void)printf("Error\nWhat is wrong with u?\n"), 1);
	return (0);
}

int	put_data(char *str, t_cub *cub, t_data_type type)
{
	if (verif_syntax(str))
		return (1);
	if (type == NORTH || type == SOUTH || type == WEST || type == EAST)
		str = str + 2;
	else if (type == FLOOR || type == CEILING)
		str++;
	while (*str == ' ' || *str == '\t')
		str++;
	if (check_dup_data(cub, type))
		return (1);
	if (type == NORTH)
		cub->textcol->no = ft_strtrim(str, "\n");
	else if (type == SOUTH)
		cub->textcol->so = ft_strtrim(str, "\n");
	else if (type == WEST)
		cub->textcol->we = ft_strtrim(str, "\n");
	else if (type == EAST)
		cub->textcol->ea = ft_strtrim(str, "\n");
	else if (type == FLOOR)
		cub->textcol->f = convert_int(str);
	else if (type == CEILING)
		cub->textcol->c = convert_int(str);
	return (0);
}

int	extract_data(char *str, t_cub *cub)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != 'N' && str[i] != 'S'
		&& str[i] != 'W' && str[i] != 'E' && str[i] != 'F' && str[i] != 'C')
	{
		printf("Error\nFile is not good\n");
		return (1);
	}
	if (str[i] == 'N')
		return (put_data(str + i, cub, NORTH));
	else if (str[i] == 'S')
		return (put_data(str + i, cub, SOUTH));
	else if (str[i] == 'W')
		return (put_data(str + i, cub, WEST));
	else if (str[i] == 'E')
		return (put_data(str + i, cub, EAST));
	else if (str[i] == 'F')
		return (put_data(str + i, cub, FLOOR));
	else if (str[i] == 'C')
		return (put_data(str + i, cub, CEILING));
	return (0);
}

int	check_data(t_cub *cub)
{
	if (!cub->textcol->no)
		return ((void)printf("Error\nNORTH texture\n"), 1);
	if (!cub->textcol->so)
		return ((void)printf("Error\nSOUTH texture\n"), 1);
	if (!cub->textcol->ea)
		return ((void)printf("Error\nEAST texture\n"), 1);
	if (!cub->textcol->we)
		return ((void)printf("Error\nWEST texture\n"), 1);
	if (cub->textcol->f == -1)
		return ((void)printf("Error\nFLOOR color\n"), 1);
	if (cub->textcol->c == -1)
		return ((void)printf("Error\nCEILING color\n"), 1);
	return (0);
}

int	get_data(t_cub *cub)
{
	char	*str;
	int		done;

	done = 0;
	str = get_next_line(cub->fd);
	if (!str)
		return (free_gnl(cub->fd), \
			(void)printf("Error\nFile is empty\n"), 1);
	while (str && !done)
	{
		if (*str != '\n' && extract_data(str, cub))
			return (free(str), free_gnl(cub->fd), 1);
		free(str);
		done = data_is_collected(cub);
		if (!done)
			str = get_next_line(cub->fd);
	}
	if (check_data(cub))
		return (free_gnl(cub->fd), 1);
	if (parse_map(cub))
		return (free_gnl(cub->fd), 1);
	if (check_last_data(cub))
		return (free_gnl(cub->fd), 1);
	return (free_gnl(cub->fd), 0);
}
