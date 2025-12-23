/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:19:13 by hadalici          #+#    #+#             */
/*   Updated: 2025/12/23 18:27:13 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	file_structure(t_map_chk *info)
{
	int	i;

	i = 0;
	while (i < info->map_start - 1)
	{
		if (find_elements("NO", info->full_file[i], '\0')
			|| find_elements("WE", info->full_file[i], '\0')
			|| find_elements("EA", info->full_file[i], '\0')
			|| find_elements("SO", info->full_file[i], '\0')
			|| find_elements(NULL, info->full_file[i], 'F')
			|| find_elements(NULL, info->full_file[i], 'C')
			|| info->full_file[i][0] == '\n')
			i++;
		else
			return (false);
	}
	return (true);
}

bool	same_direc(t_map_chk *info, int i, int n_c, int s_c)
{
	int	a[4];

	ft_memset(a, 0, sizeof(a));
	while (i < info->map_start)
	{
		if (find_elements("NO", info->full_file[i], '\0'))
			n_c++;
		if (find_elements("SO", info->full_file[i], '\0'))
			s_c++;
		if (find_elements("WE", info->full_file[i], '\0'))
			a[0]++;
		if (find_elements("EA", info->full_file[i], '\0'))
			a[1]++;
		if (find_elements(NULL, info->full_file[i], 'F'))
			a[2]++;
		if (find_elements(NULL, info->full_file[i], 'C'))
			a[3]++;
		i++;
	}
	if (n_c != 1 || s_c != 1 || a[0] != 1 || a[1] != 1
		|| a[2] != 1 || a[3] != 1)
		return (false);
	return (true);
}

bool	file_path_chk(t_map_chk *info)
{	
	if (check_file(info->nt, "NO \n") == 0)
		return (false);
	if (check_file(info->st, "SO \n") == 0)
		return (false);
	if (check_file(info->wt, "WE \n") == 0)
		return (false);
	if (check_file(info->et, "EA \n") == 0)
		return (false);
	info->nt = ft_strtrim(info->nt, "NO \n");
	info->et = ft_strtrim(info->et, "EA \n");
	info->wt = ft_strtrim(info->wt, "WE \n");
	info->st = ft_strtrim(info->st, "SO \n");
	return (true);
}

t_map_chk	*parse(char *file)
{
	t_map_chk	*info;

	info = malloc(sizeof(t_map_chk));
	ft_memset(info, 0, sizeof(t_map_chk));
	if (!check_file_name(file))
		return (free(info), printf("Error\nFile format must be \".cub\"\n"), NULL);
	if (!is_valid_file(file))
		return (free(info), printf("Error\nFile not found\n"), NULL);
	info = get_file(file, info);
	if (!get_textures_and_map(info) || !same_direc(info, 0, 0, 0))
		return (err_frees(info, 0),
			printf("Error\nEach element can only be defined once\n"), NULL);
	if (info->map[0] == NULL)
		return (err_frees(info, 0), printf("Error\nMap not found\n"), NULL);
	if (!file_structure(info))
		return (printf("Error\nWrong file format\n"), NULL);
	if (!file_path_chk(info))
		return (err_frees(info, 0), NULL);
	if (!colour_format(info) || !map_parse(info))
		return (err_frees(info, 2), NULL);
	return (info);
}
