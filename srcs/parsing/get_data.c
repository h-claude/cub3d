/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:22:15 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/14 17:33:33 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_gnl(int fd)
{
	close(fd);
	get_next_line(fd);
}

size_t	tab_len(char **tab)
{
	size_t	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

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

int32_t	convert_int(char *str)
{
	char	**splt_str;
	int		r;
	int		g;
	int		b;

	splt_str = ft_split(str, ',');
	if (tab_len(splt_str) != 3)
		return (freetab(splt_str), -1);
	r = ft_atoi(splt_str[0]);
	g = ft_atoi(splt_str[1]);
	b = ft_atoi(splt_str[2]);
	freetab(splt_str);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (-1);
	return ((r << 24) | (g << 16) | b << 8 | 255);
}

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
	if ((*str == 'N' && *(str + 1) == 'O')
		|| (*str == 'S' && *(str + 1) == 'O')
		|| (*str == 'W' && *(str + 1) == 'E')
		|| (*str == 'E' && *(str + 1) == 'A'))
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
		printf("Error\nMap is broken\n");
		return (1);
	}
	if (str[i] == 'N')
		return (put_data(str, cub, NORTH));
	else if (str[i] == 'S')
		return (put_data(str, cub, SOUTH));
	else if (str[i] == 'W')
		return (put_data(str, cub, WEST));
	else if (str[i] == 'E')
		return (put_data(str, cub, EAST));
	else if (str[i] == 'F')
		return (put_data(str, cub, FLOOR));
	else if (str[i] == 'C')
		return (put_data(str, cub, CEILING));
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
		return (free_gnl(cub->fd), 1);//fail
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
	return (0);
}
