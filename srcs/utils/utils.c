/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:54:17 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/19 17:35:25 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	freetab(char **tab, size_t len, bool no_len)
{
	size_t	i;

	i = 0;
	if (no_len)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
		return ;
	}
	while (i != len)
		free(tab[i++]);
	free(tab);
}

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

size_t	lstlen(t_list *lst)
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
