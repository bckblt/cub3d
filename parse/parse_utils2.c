/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 01:09:29 by hadalici          #+#    #+#             */
/*   Updated: 2025/11/23 04:50:29 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_char(char a)
{
	if (a != '0' && a != '1' && a != 'N' && a != 'W' && a != 'S'
		&& a != 'E' && a != '\n' && a != '\0' && a != ' ')
	{
		return (false);
	}
	return (true);
}

bool	is_valid_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	else
		return (true);
	close(fd);
}

bool	check_file(char *file_name, char *to_find)
{
	char	*tmp;

	tmp = ft_strtrim(file_name, to_find);
	if (!is_valid_file(tmp))
	{
		free(tmp);
		printf("textures not found\n");
		return (false);
	}
	free(tmp);
	return (true);
}
