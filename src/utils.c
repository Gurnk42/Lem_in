/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 19:25:08 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/23 14:27:21 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		ft_split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

int		ft_is_in_split(char **split, char *str)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		if (ft_strcmp(split[i], str) == 0)
			return (1);
		i++;
	}
	return (0);
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
	return (ret);
}

void	ft_error_exit(const char *error)
{
	if (ERROR_DESC == 1)
	{
		ft_putstr_fd("\033[31m", 2);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\033[0m", 2);
	}
	else
		ft_putstr_fd("ERROR", 1);
	exit(-1);
}
