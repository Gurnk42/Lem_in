/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:05:08 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/19 19:56:05 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_parse(t_list **lst, t_env *e)
{
	char	*line;
	char	**split;
	int		i;
	t_room	*tmp;

	tmp = NULL;
	i = 0;
	while (get_next_line(0, &line))
	{
		if (*line != '#')
		{
			if (i == 0)
				e->ants_nb = ft_atoi(line);
			else
			{
				split = ft_strsplit(line, ' '); // Free dat shit later

				if ((tmp = (t_room *)malloc(sizeof(t_room))) == NULL)
					ft_error_exit("Cannot allocate list content\n");
				tmp->name = ft_strdup(split[0]);
				tmp->pos.x = ft_atoi_error_exit(split[1], "INT OVERFLOW. Exit.\n");
				tmp->pos.x = ft_atoi_error_exit(split[2], "INT OVERFLOW. Exit.\n");
				tmp->ants_there = 0;
				tmp->tunnels = NULL;
				ft_lstadd(lst, ft_lstnew((void *)tmp, sizeof(t_room)));
			}
			i++;
		}
	}
}

int main(int argc, char **argv)
{
	t_list	*lst;
	t_env	env;

	(void)argc;
	(void)argv;
	if ((lst = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (0); //Should print error there.
	lst = NULL;
	ft_parse(&lst, &env);

	return (0);
}
