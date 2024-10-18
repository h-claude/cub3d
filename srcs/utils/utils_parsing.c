/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:49:29 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/19 00:54:39 by hclaude          ###   ########.fr       */
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


