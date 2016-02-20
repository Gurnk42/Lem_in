/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:05:45 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/20 15:38:35 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# define ERROR_DESC 1
# define DEBUG 1
# define START 1
# define END -1

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
	t_list			*tunnels;
	int				checked;
	int				distance;
}					t_room;

typedef struct		s_env
{
	int				ants_nb;
	char			*start;
	char			*end;
	t_list			**shortest_path;
}					t_env;

void				ft_error_exit(const char *error);
int					ft_split_len(char **split);
char				**ft_split_join_free(char **split, char *str);
int					ft_is_in_split(char **split, char *str);

#endif
