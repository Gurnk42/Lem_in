/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:05:45 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/19 20:06:00 by ebouther         ###   ########.fr       */
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
	struct s_room	**tunnels;
}					t_room;

typedef struct		s_env
{
	int				ants_nb;
}					t_env;

void				ft_error_exit(const char *error);

#endif
