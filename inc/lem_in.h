/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:05:45 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/23 11:40:26 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# define ERROR_DESC 0
# define DEBUG 0
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
	int				start_end;
	t_list			*tunnels;
	int				checked;
}					t_room;

typedef struct		s_path
{
	char			*name;
	int				ant;
	struct s_path	*previous;
}					t_path;

typedef struct		s_env
{
	int				ants_nb;
	char			*start;
	char			*end;
	t_list			*shortest_path;
	int				len;
	t_list			**lst;
}					t_env;

/*
** free.c
*/
void				ft_free_tunnels(t_list *lst);
void				ft_free_main_list(t_list **lst);
void				ft_free_split(char **split);

/*
** utils.c / utils_2.c
*/
void				ft_error_exit(const char *error);
t_list				*ft_search_for_node(char *name, t_list **lst);
void				ft_print_all_paths(t_env *e);
void				ft_print_list_content(t_list *lst);
int					ft_is_in_split(char **split, char *str);
char				**ft_split_join_free(char **split, char *str);
int					ft_split_len(char **split);

/*
** algo.c
*/
int					ft_get_tunnel(t_list *tunnels, t_list **next_rooms,
						char *name, t_env *e);
int					ft_get_shortest_path_len(t_list *node, t_env *e);

#endif
