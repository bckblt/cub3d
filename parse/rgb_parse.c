/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 04:48:30 by hadalici          #+#    #+#             */
/*   Updated: 2025/11/23 05:22:17 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	range_chk(char **colour)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (colour[i])
	{
		j = ft_atoi(colour[i]);
		if (j < 0 || j > 255)
			return (false);
		i++;
	}
	return (true);
}

int	get_rgb(char **str_rgb)
{
	int	a[3];
	int	i;
	int	color;

	i = 0;
	while (i < 3)
	{
		a[i] = ft_atoi(str_rgb[i]);
		i++;
	}
	color = (a[0] << 16) | (a[1] << 8) | a[2];
	return (color);
}

bool	valid_color(t_map_chk *info, char *color, char *to_find, char key)
{
	char	*tmp;
	char	**tmp2;
	int		i;

	i = 0;
	tmp = ft_strtrim(color, to_find);
	tmp2 = ft_split(tmp, ',');
	while (tmp2[i])
		i++;
	if (i >= 4 || !rgb_chk(tmp2) || !comma_chk(tmp) || !tmp2[2])
	{
		free(tmp);
		free_dp(tmp2);
		return (false);
	}
	if (key == 'F')
		info->F_C = get_rgb(tmp2);
	if (key == 'C')
		info->C_C = get_rgb(tmp2);
	free_dp(tmp2);
	free(tmp);
	return (true);
}

bool	colour_format(t_map_chk *info)
{
	if (!valid_color(info, info->F, "F \n", 'F'))
	{
		printf("Colour format must be RGB\n");
		return (false);
	}
	if (!valid_color(info, info->C, "C \n", 'C'))
	{
		printf("Colour format must be RGB\n");
		return (false);
	}
	return (true);
}

bool	rgb_chk(char **colour)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (colour[i])
	{
		j = 0;
		while (colour[i][j])
		{
			if (!((colour[i][j] <= '9' && colour[i][j] >= '0')
			|| colour[i][j] >= ' '))
				return (false);
			j++;
		}
		i++;
	}
	if (!range_chk(colour))
		return (false);
	return (true);
}
