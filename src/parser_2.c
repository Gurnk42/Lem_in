/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 12:23:56 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/23 17:41:39 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_command_error(t_parse *p)
{
	if (p->s_e[0] != -1 && p->s_e[1] != -1)
	{
		if (ft_abs(p->s_e[0] - p->s_e[1]) == 1)
			ft_error_exit("Bad command format.\n");
	}
}

void	ft_init_parse(t_parse *p)
{
	p->iter = 0;
	p->i = 0;
	p->start_end = 0;
	p->s_e[0] = -1;
	p->s_e[1] = -1;
}
