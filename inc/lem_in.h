/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:05:45 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/19 23:11:06 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft.h"

typedef struct		s_coords
{
	int				x;
	int				y;

}					t_coords;

typedef struct		s_room
{
	char			*name;
	t_coords		pos;
	int				ants_there;
	int				start_end;
	char			**tunnels;
}					t_room;

typedef struct		s_env
{
	int				ants_nb;
}					t_env;

void				ft_error_exit(const char *error);
int					ft_split_len(char **split);
char				**ft_split_join_free(char **split, char *str);
int					ft_is_in_split(char **split, char *str);

#endif
