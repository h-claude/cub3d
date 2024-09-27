/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:47:24 by hclaude           #+#    #+#             */
/*   Updated: 2024/09/27 16:37:56 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H

# define CUB_H

# include "../turbo_libft/include/libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_textcol
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int32_t	f;
	int32_t	c;
}	t_textcol;

typedef struct cub
{
	int					fd;
	char				**map;
	struct s_textcol 	*textcol;
}	t_cub;

#endif