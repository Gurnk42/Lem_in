/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 12:23:56 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/23 13:19:30 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_link_rooms_core(t_list *tmp, char **split)
{
	int		count;

	count = 0;
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
		ft_error_exit("Bad room name in room links.\n");
}

void		ft_link_rooms(char *line, t_list **lst)
{
	t_list	*begin;
	t_list	*tmp;
	char	**split;

	begin = *lst;
	tmp = *lst;
	split = ft_strsplit(line, '-');
	if (ft_strcmp(split[0], split[1]) == 0)
		ft_error_exit("Room is linked to itself.\n");
	if (ft_split_len(split) > 2)
		ft_error_exit("Bad format for room links.\n");
	ft_link_rooms_core(tmp, split);
}

void		ft_get_rooms(int *start_end, char *line, t_env *e)
{
	t_room	*tmp;
	char	**split;

	(void)e;
	tmp = NULL;
	split = ft_strsplit(line, ' ');
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

static void	ft_parse_core(char *line, int *start_end, int *i, t_env *e)
{
	int	n;

	if (*line != '#')
	{
		if (*i == 0)
		{
			n = 0;
			if (*line == '\0')
				ft_error_exit("Bad input format.\n");
			while (line[n])
				if (!ft_isdigit(line[n++]))
					ft_error_exit("Bad input format.\n");
			e->ants_nb = ft_atoi(line);
		}
		else
		{
			if (ft_strchr(line, ' ') != NULL)
				ft_get_rooms(start_end, line, e);
			else
				ft_link_rooms(line, e->lst);
		}
		(*i)++;
	}
}

void		ft_parse(t_env *e)
{
	char	*line;
	int		i;
	int		start_end;
	int		ret;

	i = 0;
	start_end = 0;
	while ((ret = get_next_line(0, &line)) == 1)
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
		ft_parse_core(line, &start_end, &i, e);
		ft_strdel(&line);
	}
	if (ret == -1 || i == 0)
		ft_error_exit("Bad input.\n");
}
