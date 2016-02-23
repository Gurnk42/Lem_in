/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:05:08 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/23 11:39:18 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_link_rooms(char *line, t_list **lst)
{
	t_list	*begin;
	t_list	*tmp;
	char	**split;
	int		count;

	count = 0;
	begin = *lst;
	tmp = *lst;
	split = ft_strsplit(line, '-'); // Free dat shit later
	if (ft_strcmp(split[0], split[1]) == 0)
		ft_error_exit("Room is linked to itself.\n");
	if (ft_split_len(split) > 2)
		ft_error_exit("Bad format for room links.\n");
	while (tmp != NULL)
	{
		if (ft_strcmp(((t_room *)(tmp->content))->name, split[0]) == 0)

		{
			ft_lstadd(&(((t_room *)(tmp->content))->tunnels),
					ft_lstnew((void *)ft_strdup(split[1]), sizeof(char *)));
			count++;
		}
		else if (ft_strcmp(((t_room *)(tmp->content))->name, split[1]) == 0)
		{
			ft_lstadd(&(((t_room *)(tmp->content))->tunnels),
					ft_lstnew((void *)ft_strdup(split[0]), sizeof(char *)));
			count++;
		}
		tmp = tmp->next;
	}
	if (count != 2)
	{
		ft_printf("LINE : '%s'\n", line);
		ft_error_exit("Bad room name in room links.\n");
	}
}

static void	ft_get_rooms(int *start_end, char *line, t_env *e)
{
	t_room	*tmp;
	char	**split;

	(void)e;
	tmp = NULL;
	split = ft_strsplit(line, ' '); // Free dat shit later
	if ((tmp = (t_room *)malloc(sizeof(t_room))) == NULL)
		ft_error_exit("Cannot allocate list content\n");
	tmp->name = ft_strdup(split[0]);
	tmp->pos.x = ft_atoi_error_exit(split[1], "INT OVERFLOW. Exit.\n");
	tmp->pos.x = ft_atoi_error_exit(split[2], "INT OVERFLOW. Exit.\n");
	tmp->checked = 0;
	tmp->tunnels = NULL;
	if (*start_end == 1 || *start_end == -1)
	{
		(*start_end == 1) ? (e->start = ft_strdup(tmp->name)) : 
			(e->end = ft_strdup(tmp->name));
		tmp->start_end = *start_end;
		*start_end = 0;
	}
	ft_free_split(split);
	ft_lstadd(e->lst, ft_lstnew((void *)tmp, sizeof(t_room)));
}

static void	ft_parse(t_env *e)
{
	char	*line;
	int		i;
	int		start_end;

	i = 0;
	start_end = 0;
	while (get_next_line(0, &line))
	{
		if (ft_strncmp(line, "##", 2) == 0)
		{
			if (ft_strcmp(line, "##start") == 0)
				start_end = 1;
			else if (ft_strcmp(line, "##end") == 0)
				start_end = -1;
			else
				ft_error_exit("Bad line starting with \"##\"");
		}
		if (*line != '#')
		{
			if (i == 0)
				e->ants_nb = ft_atoi(line);
			else
			{
				if (ft_strchr(line, ' ') != NULL)
					ft_get_rooms(&start_end, line, e);
				else
					ft_link_rooms(line, e->lst);
			}
			i++;
		}
		ft_strdel(&line);
	}
}

static char	*ft_get_pos_name(t_list	*lst, int pos)
{
	int i;

	i = 1;
	while (lst != NULL)
	{
		if (i == pos)
			return ((char *)lst->content);
		lst = lst->next;
		i++;
	}
	return (NULL);
}

static void	ft_print_ants(t_env *e)
{
	int		i;
	int 	n;
	int		ants_pos[e->ants_nb];
	char	*name;

	i = 0;
	n = 0;
	while (i < (e->ants_nb))
		ants_pos[i++] = n--;
	while ((i = 0) == 0)
	{
		while (i < e->ants_nb)
		{
			ants_pos[i]++;
			if (ants_pos[i] > 0)
			{
				if ((name = ft_get_pos_name(e->shortest_path, ants_pos[i])) != NULL)
					ft_printf("L%d-%s ", i + 1, name);
				else if (i + 1 == e->ants_nb)
					return ;
			}
			i++;
		}
		ft_putchar('\n');
	}
}

int main(int argc, char **argv)
{
	t_env	env;

	(void)argc;
	(void)argv;
	if ((env.lst = (t_list **)malloc(sizeof(t_list *))) == NULL)
		ft_error_exit("Cannot allocate memory.\n");
	*(env.lst) = NULL;
	env.shortest_path = NULL;
	ft_parse(&env);
	if (DEBUG == 1)
		ft_print_list_content((*(env.lst)));
	ft_print_all_paths(&env);
	ft_free_main_list(env.lst);
	ft_memdel((void **)&env.lst);
	ft_print_ants(&env);
	return (0);
}
