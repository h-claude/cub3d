/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:54:17 by hclaude           #+#    #+#             */
/*   Updated: 2024/10/20 16:45:30 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_number(char *str)
{
	bool	there_is_digit;

	there_is_digit = false;
	while (*str == ' ' || *str == '\t')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			if (*str == '\n' && there_is_digit)
				return (1);
			return (0);
		}
		there_is_digit = true;
		str++;
	}
	return (1);
}

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
