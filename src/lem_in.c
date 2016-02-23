/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:05:08 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/23 15:00:15 by ebouther         ###   ########.fr       */
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
	t_print p;

	p.i = 0;
	p.n = 0;
	if ((p.ants_pos = (int *)malloc(sizeof(int) * e->ants_nb)) == NULL)
		ft_error_exit("Cannot allocate memory.\n");
	while (p.i < (e->ants_nb))
		p.ants_pos[p.i++] = p.n--;
	while ((p.i = 0) == 0)
	{
		while (p.i < e->ants_nb)
		{
			if (++(p.ants_pos[p.i]) > 0)
			{
				if ((p.name = ft_name(e->shortest_path,
						p.ants_pos[p.i])) != NULL)
					ft_printf("L%d-%s ", p.i + 1, p.name);
				else if (p.i + 1 == e->ants_nb)
					return ;
			}
			p.i++;
		}
		ft_putchar('\n');
	}
	ft_memdel((void **)&p.ants_pos);
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
