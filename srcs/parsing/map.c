/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:31:26 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/19 19:05:34 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	lst_add_node(t_list *lst, char *content)
{
	while (lst->next)
	{
		lst = lst->next;
	}
	if (!lst->content)
	{
		lst->content = ft_strdup(content);
		if (!lst->content)
			return (1);
	}
	else
	{
		lst->next = ft_lstnew((void *)content);
		if (!lst->next)
		{
			printf("Error\nFailed malloc\n");
			return (1);
		}
	}
	return (0);
}

int	lst_to_cub(t_cub *cub, t_list **lst)
{
	size_t		i;
	t_list		*tmp_lst;

	tmp_lst = *lst;
	i = 0;
	cub->map_len = lstlen(*lst);
	if (cub->map_len > 1500)
		return (free_lst(lst), (void)printf("Error\nMap too big\n"), 1);
	cub->map = malloc(sizeof(char *) * (cub->map_len + 1));
	if (!cub->map)
		return (free_lst(lst), (void)printf("Error\nFailed malloc\n"), 1);
	cub->map[cub->map_len] = NULL;
	while (tmp_lst && i != cub->map_len)
	{
		cub->map[i] = ft_strdup((char *)tmp_lst->content);
		if (!cub->map[i])
			return (free_lst(lst), (void)printf("Error\nFailed malloc\n"), 1);
		tmp_lst = tmp_lst->next;
		i++;
	}
	return (free_lst(lst), 0);
}

char	*skip_line(int fd)
{
	char	*str;

	str = get_next_line(fd);
	while (str && *str == '\n')
	{
		free(str);
		str = get_next_line(fd);
	}
	return (str);
}

int	parse_map(t_cub *cub)
{
	t_list	*lst;
	char	*str;

	str = skip_line(cub->fd);
	if (!str)
		return ((void)printf("Error\nFile is broken\n"), 1);
	lst = malloc(sizeof(t_list));
	if (!lst)
		return ((void)printf("Error\nFailed malloc\n"), free(str), 1);
	lst->content = NULL;
	lst->next = NULL;
	while (str && *str != '\n')
	{
		if (*str != '\n')
		{
			if (lst_add_node(lst, str))
				return (free_lst(&lst), \
					printf("Error\nFailed malloc\n"), free(str), 1);
		}
		free(str);
		str = get_next_line(cub->fd);
	}
	if (str)
		free(str);
	return (lst_to_cub(cub, &lst));
}
