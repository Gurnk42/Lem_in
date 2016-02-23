/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:05:08 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/23 12:51:21 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*ft_name(t_list *lst, int pos)
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
	int		n;
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
				if ((name = ft_name(e->shortest_path, ants_pos[i])) != NULL)
					ft_printf("L%d-%s ", i + 1, name);
				else if (i + 1 == e->ants_nb)
					return ;
			}
			i++;
		}
		ft_putchar('\n');
	}
}

int			main(int argc, char **argv)
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
