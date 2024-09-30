/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:22:15 by hclaude           #+#    #+#             */
/*   Updated: 2024/09/30 18:05:24 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	data_is_collected(t_cub *cub)
{
	if (!cub->textcol->ea)
		return (0);
	if (!cub->textcol->we)
		return (0);
	if (!cub->textcol->no)
		return (0);
	if (!cub->textcol->so)
		return (0);
	if (cub->textcol->c == -1)
		return (0);
	if (cub->textcol->f == -1)
		return (0);
	return (1);
}

int	verif_syntax(char *str)
{
	if ((*str == 'N' && *(str + 1) == 'O') ||
		(*str == 'S' && *(str + 1) == 'O') ||
		(*str == 'W' && *(str + 1) == 'E') ||
		(*str == 'E' && *(str + 1) == 'A'))
    {
        str += 2;
        if (*str == ' ' || *str == '\t')
            return (0);
    }
	else if (*str == 'F' || *str == 'C')
	{
		str++;
		if (*str == ' ' || *str == '\t')
			return (0);
	}
	return (1);
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
	// proteger malloc
	if (type == NORTH)
		cub->textcol->no = ft_strdup(str);
	else if (type == SOUTH)
		cub->textcol->so = ft_strdup(str);
	else if (type == WEST)
		cub->textcol->we = ft_strdup(str);
	else if (type == EAST)
		cub->textcol->ea = ft_strdup(str);
	else if (type == FLOOR)
		cub->textcol->f = 0;//convert_int(str); // convert string to int32
	else if (type == CEILING)
		cub->textcol->c = 0;//convert_int(str); // convert string to int32
	return (0);
}

int	extract_data(char *str, t_cub *cub)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != 'N' && str[i] != 'S' &&
		str[i] != 'W' && str[i] != 'E' && str[i] != 'F' && str[i] != 'C')
	{
		printf("Error\nMap is broken\n");
		return (1);
	}
	if (str[i] == 'N')
		put_data(str, cub, NORTH);
	else if (str[i] == 'S')
		put_data(str, cub, SOUTH);
	else if (str[i] == 'W')
		put_data(str, cub, WEST);
	else if (str[i] == 'E')
		put_data(str, cub, EAST);
	else if (str[i] == 'F')
		put_data(str, cub, FLOOR);
	else if (str[i] == 'C')
		put_data(str, cub, CEILING);
	return (0);
}

int	get_data(t_cub *cub)
{
	char	*str;

	str = get_next_line(cub->fd);
	if (!str)
		return (1);//fail
	while (str && !data_is_collected(cub))
	{
		if (*str != '\n' && extract_data(str, cub))
			return (free(str), 1);
		free(str);
		str = get_next_line(cub->fd);
	}
	parse_map(cub);
	return (0);
}
