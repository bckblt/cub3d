/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:19:13 by hadalici          #+#    #+#             */
/*   Updated: 2025/11/23 05:46:26 by hadalici         ###   ########.fr       */
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
	int	w_c;
	int	e_c;

	w_c = 0;
	e_c = 0;
	while (i < info->map_start - 1)
	{
		if (find_elements("NO", info->full_file[i], '\0'))
			n_c++;
		if (find_elements("SO", info->full_file[i], '\0'))
			s_c++;
		if (find_elements("WE", info->full_file[i], '\0'))
			w_c++;
		if (find_elements("EA", info->full_file[i], '\0'))
			e_c++;
		i++;
	}
	if (n_c != 1 || w_c != 1 || e_c != 1 || s_c != 1)
		return (false);
	return (true);
}

bool	file_path_chk(t_map_chk *info)
{	
	if (check_file(info->NT, "NO \n") == 0)
		return (false);
	if (check_file(info->ST, "SO \n") == 0)
		return (false);
	if (check_file(info->WT, "WE \n") == 0)
		return (false);
	if (check_file(info->ET, "EA \n") == 0)
		return (false);
	info->NT = ft_strtrim(info->NT, "NO \n");
	info->ET = ft_strtrim(info->ET, "EA \n");
	info->WT = ft_strtrim(info->WT, "WE \n");
	info->ST = ft_strtrim(info->ST, "SO \n");
	return (true);
}

t_map_chk	*parse(char *file)
{
	t_map_chk	*info;

	info = malloc(sizeof(t_map_chk));
	ft_memset(info, 0, sizeof(t_map_chk));
	if (!check_file_name(file))
		return (free(info), printf("File format must be \".cub\"\n"), NULL);
	if (!is_valid_file(file))
		return (printf("File not found\n"), NULL);
	info = get_file(file, info);
	if (!get_textures_and_map(info) || !same_direc(info, 0, 0, 0))
		return (err_frees(info, 0),
			printf("Each element can only be defined once\n"), NULL);
	if (info->map[0] == NULL)
		return (err_frees(info, 0), printf("Map not found\n"), NULL);
	if (!file_structure(info))
		return (printf("Wrong file format\n"), NULL);
	if (!file_path_chk(info))
		return (err_frees(info, 0), NULL);
	if (!colour_format(info) || !map_parse(info))
		return (err_frees(info, 2), NULL);
	return (info);
}
