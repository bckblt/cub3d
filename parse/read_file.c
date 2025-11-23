/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:19:23 by hadalici          #+#    #+#             */
/*   Updated: 2025/11/23 05:21:43 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_chk	*get_file(char *file, t_map_chk *info)
{
	char	*line;
	int		len;
	int		fd;

	len = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}
	info->full_file = malloc(sizeof(char *) * (len + 1));
	len = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		info->full_file[len] = line;
		len++;
		line = get_next_line(fd);
	}
	info->full_file[len] = NULL;
	return (info);
}

void	get_map(t_map_chk *info, int i)
{
	int	temp;
	int	len;

	len = 0;
	while (info->full_file[i] && (info->full_file[i][0] == '\n'))
		i++;
	temp = i;
	info->map_start = i;
	while (info->full_file[temp])
	{
		len++;
		temp++;
	}
	info->map = malloc(sizeof(char *) * (len + 1));
	if (!info->map)
		return ;
	len = 0;
	while (info->full_file[i])
	{
		info->map[len] = ft_strtrim(info->full_file[i], "\n");
		i++;
		len++;
	}
	info->map[len] = NULL;
}

bool	find_elements(char *key, char *line, char a)
{
	int	i;

	i = 0;
	if (!key)
	{
		while (line[i])
		{
			if (line[i] == a)
				return (true);
			i++;
		}
	}
	else
	{
		while (line[i])
		{
			if (line[i] == key[0] && line[i + 1] == key[1])
				return (true);
			i++;
		}
	}
	return (false);
}

static int	parse_element_line(char *line, t_map_chk *info)
{
	if (find_elements("NO", line, '\0'))
		info->NT = line;
	else if (find_elements("SO", line, '\0'))
		info->ST = line;
	else if (find_elements("EA", line, '\0'))
		info->ET = line;
	else if (find_elements("WE", line, '\0'))
		info->WT = line;
	else if (find_elements(NULL, line, 'F'))
		info->F = line;
	else if (find_elements(NULL, line, 'C'))
		info->C = line;
	else
		return (0);
	return (1);
}

bool	get_textures_and_map(t_map_chk *info)
{
	int	i;
	int	arg_count;
	int	map_start_idx;

	i = 0;
	arg_count = 0;
	map_start_idx = 0;
	while (info->full_file[i])
	{
		if (arg_count < 6)
			arg_count += parse_element_line(info->full_file[i], info);
		if (arg_count == 6 && map_start_idx == 0)
			map_start_idx = i + 1;
		i++;
	}
	if (arg_count != 6)
		return (false);
	get_map(info, map_start_idx);
	return (true);
}
