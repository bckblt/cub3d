/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:18:36 by hadalici          #+#    #+#             */
/*   Updated: 2025/11/23 01:00:09 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_marks(char **cp_map, int x, int y)
{
	cp_map[y][x] = '*';
	if (y > 0 && cp_map[y - 1][x] && cp_map[y - 1][x] != '1'
		&& cp_map[y - 1][x] != '*')
		put_marks(cp_map, x, y - 1);
	if (cp_map[y + 1] && cp_map[y + 1][x] && cp_map[y + 1][x] != '1'
		&& cp_map[y + 1][x] != '*')
		put_marks(cp_map, x, y + 1);
	if (x > 0 && cp_map[y][x - 1] && cp_map[y][x - 1] != '1'
		&& cp_map[y][x - 1] != '*')
		put_marks(cp_map, x - 1, y);
	if (cp_map[y][x + 1] && cp_map[y][x + 1] != '1'
		&& cp_map[y][x + 1] != '*')
		put_marks(cp_map, x + 1, y);
}

bool	space_chk(int x, int y, char **cp_map)
{
	if (cp_map[x][y] == '*')
	{
		if (x == 0 || y == 0 || cp_map[x + 1] == NULL
			|| cp_map[x][y + 1] == '\0')
			return (false);
		if (cp_map[x + 1][y] != '1' && cp_map[x + 1][y] != '*')
			return (false);
		if (cp_map[x - 1][y] != '1' && cp_map[x - 1][y] != '*')
			return (false);
		if (cp_map[x][y + 1] != '1' && cp_map[x][y + 1] != '*')
			return (false);
		if (cp_map[x][y - 1] != '1' && cp_map[x][y - 1] != '*')
			return (false);
	}
	return (true);
}

bool	wall_check(t_map_chk *info)
{
	int		x;
	int		y;
	char	**cp_map;

	x = 0;
	y = 0;
	cp_map = map_copy(info->map);
	put_marks(cp_map, info->p_x, info->p_y);
	while (cp_map[x])
	{
		y = 0;
		while (cp_map[x][y])
		{
			if (!space_chk(x, y, cp_map))
				return (free_dp(cp_map), printf("Error : Invalid map\n"), false);
			if (cp_map[x][y] != '1' && cp_map[x][y] != '*'
				&& cp_map[x][y] != '\n' && cp_map[x][y] != '\0'
				&& cp_map[x][y] != '0' && cp_map[x][y] != ' ')
				return (free_dp(cp_map), printf("Error : Invalid map\n"), false);
			y++;
		}
		x++;
	}
	free_dp(cp_map);
	return (true);
}

bool	map_parse(t_map_chk *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (!is_valid_char(info->map[i][j]))
			{
				printf("Invalid char in map\n");
				return (false);
			}
			j++;
		}
		i++;
	}
	if (!player_chk(info))
		return (false);
	if (!wall_check(info) || !move_chk(info))
		return (false);
	return (true);
}
