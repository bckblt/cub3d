/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:59:29 by hadalici          #+#    #+#             */
/*   Updated: 2025/11/23 01:00:29 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	player_c(t_map_chk *info)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	j = 0;
	c = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (info->map[i][j] == 'N' || info->map[i][j] == 'E'
				|| info->map[i][j] == 'S'
				|| info->map[i][j] == 'W')
			{
				c++;
			}
			j++;
		}
		i++;
	}
	if (c != 1)
		return (false);
	return (true);
}

bool	player_chk(t_map_chk *info)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (info->map[i][j] == 'N' || info->map[i][j] == 'E'
				|| info->map[i][j] == 'S'
				|| info->map[i][j] == 'W')
			{
				info->p_x = j;
				info->p_y = i;
			}
			j++;
		}
		i++;
	}
	if (info->p_x == 0 || info->p_y == 0 || !player_c(info))
		return (printf("Player position not correct\n"), false);
	return (true);
}

bool	move_chk(t_map_chk *info)
{
	if (info->map[info->p_y - 1][info->p_x] == '1'
		&& info->map[info->p_y + 1][info->p_x] == '1'
		&& info->map[info->p_y][info->p_x - 1] == '1'
		&& info->map[info->p_y][info->p_x + 1] == '1')
	{
		printf("No movement area for player\n");
		return (false);
	}
	return (true);
}
