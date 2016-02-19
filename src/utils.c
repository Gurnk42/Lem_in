/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 19:25:08 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/19 23:01:40 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

char	**ft_split_join_free(char **split, char *str)
{
	int		len;
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	len = ft_split_len(split);
	if ((ret = (char **)malloc(sizeof(char *) * (len + 2))) == NULL)
		ft_error_exit("Cannot allocate memory in ft_split_join_free().\n");
	while (split[i] != NULL)
	{
		ret[i] = ft_strdup(split[i]);
		i++;
	}
	ret[i] = ft_strdup(str);
	ret[i + 1] = NULL;
	//FREE SPLIT THERE !!!
	return (ret);
}

void	ft_error_exit(const char *error)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\033[0m", 2);
	exit(-1);
}
