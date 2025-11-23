/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:19:00 by hadalici          #+#    #+#             */
/*   Updated: 2025/11/23 04:49:44 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	comma_chk(char *str)
{
	int	i;

	i = 0;
	if (str[i] == ',' || str[ft_strlen(str) - 1] == ',')
		return (false);
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (false);
		i++;
	}
	return (true);
}

bool	check_file_name(char *file)
{
	int		i;
	char	*tmp;

	i = 0;
	if (file[0] == '.')
		return (false);
	while (file[i])
	{
		if (file[i] != '.')
			i++;
		else
		{
			if (file[i + 1] != 'c' || file[i + 2] != 'u'
				|| file[i + 3] != 'b' || file[i + 4] != '\0')
				return (false);
			else
				return (true);
		}
	}
	tmp = ft_strchr(file, '.');
	if (tmp == NULL)
		return (false);
	return (true);
}

void	free_dp(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**map_copy(char **map)
{
	char	**cp_map;
	int		i;

	i = 0;
	while (map[i])
		i++;
	cp_map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (map[i])
	{
		cp_map[i] = ft_strdup(map[i]);
		i++;
	}
	cp_map[i] = NULL;
	return (cp_map);
}
