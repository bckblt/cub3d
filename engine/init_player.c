/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:29:13 by bakarabu          #+#    #+#             */
/*   Updated: 2025/12/21 20:22:15 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_vertical_direction(char dir, t_game *game, int y, int x)
{
	if (dir == 'N')
	{
		game->player->dirx = 0;
		game->player->diry = -1;
		game->planex = 0.66;
		game->planey = 0;
	}
	else if (dir == 'S')
	{
		game->player->dirx = 0;
		game->player->diry = 1;
		game->planex = -0.66;
		game->planey = 0;
	}
	game->info->map[y][x] = '0';
	return ;
}

void	set_horizonal_direction(char dir, t_game *game, int y, int x)
{
	if (dir == 'E')
	{
		game->player->dirx = 1;
		game->player->diry = 0;
		game->planex = 0;
		game->planey = 0.66;
	}
	else if (dir == 'W')
	{
		game->player->dirx = -1;
		game->player->diry = 0;
		game->planex = 0;
		game->planey = -0.66;
	}
	game->info->map[y][x] = '0';
	return ;
}

void	init_player(t_game *game)
{
	int		x;
	int		y;
	char	**map;

	map = game->info->map;
	x = game->info->p_x;
	y = game->info->p_y;
	if (map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'E' || map[y][x] == 'W')
	{
		game->player->x = x + 0.5;
		game->player->y = y + 0.5;
		if (map[y][x] == 'N')
			set_vertical_direction('N', game, y, x);
		else if (map[y][x] == 'S')
			set_vertical_direction('S', game, y, x);
		else if (map[y][x] == 'E')
			set_horizonal_direction('E', game, y, x);
		else if (map[y][x] == 'W')
			set_horizonal_direction('W', game, y, x);
		return ;
	}
}
