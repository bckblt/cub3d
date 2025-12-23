/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:19:00 by hadalici          #+#    #+#             */
/*   Updated: 2025/12/23 16:17:29 by hadalici         ###   ########.fr       */
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
	int	len;

	if (!file)
		return (false);
	len = ft_strlen(file);
	if (len < 5)
		return (false);
	if (ft_strncmp(file + len - 4, ".cub", 4) == 0)
		return (true);
	return (false);
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
