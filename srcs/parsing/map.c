/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:31:26 by hclaude           #+#    #+#             */
/*   Updated: 2024/09/30 22:33:54 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	free_lst(t_list **lst)
{
	t_list	*tmp_lst;

	while (*lst)
	{
		tmp_lst = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp_lst;
	}
}

size_t lstlen(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

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
	int	i;
	t_list	*tmp_lst;

	tmp_lst = *lst;
	i = 0;
	cub->map = malloc(sizeof(char *) * lstlen(*lst) + 1);
	if (!cub->map)
		return (free_lst(lst), (void)printf("Error\nFailed malloc\n"), 1);
	cub->map[lstlen(*lst) + 1] = NULL;
	while (tmp_lst)
	{
		cub->map[i] = ft_strdup((char *)tmp_lst->content);
		if (!cub->map[i])
			return (free_lst(lst), (void)printf("Error\nFailed malloc\n"), 1);
		tmp_lst = tmp_lst->next;
		i++;
	}
	free_lst(lst);
	return (0);
}

int	parse_map(t_cub *cub)
{
	t_list	*lst;
	char	*str;

	str = get_next_line(cub->fd);
	if (!str)
		return ((void)printf("Error\nFile is broken\n"), 1);	
	lst = malloc(sizeof(t_list));
	if (!lst)
		return ((void)printf("Error\nFailed malloc\n"), free(str), 1);
	lst->content = NULL;
	lst->next = NULL;
	while (str)
	{
		if (*str != '\n')
		{
			if (lst_add_node(lst, str))
				return (free_lst(&lst), printf("Error\nFailed malloc\n"), 1);
		}
		free(str);
		str = get_next_line(cub->fd);
	}
	return (lst_to_cub(cub, &lst));
}
