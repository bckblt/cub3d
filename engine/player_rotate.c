/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:14:37 by bakarabu          #+#    #+#             */
/*   Updated: 2025/12/21 20:23:13 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(double x, double y, t_game *game)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || my < 0 || mx >= game->info->max_x || my >= game->info->max_y)
		return (1);
	return (game->info->map[my][mx] == '1');
}

void	rotate_left(t_game *game)
{
	double	rotspeed;
	double	olddirx;
	double	oldplanex;

	rotspeed = 0.05;
	olddirx = game->player->dirx;
	oldplanex = game->planex;
	game->player->dirx = game->player->dirx * cos(-rotspeed)
		- game->player->diry * sin(-rotspeed);
	game->player->diry = olddirx * sin(-rotspeed)
		+ game->player->diry * cos(-rotspeed);
	game->planex = game->planex * cos(-rotspeed)
		- game->planey * sin(-rotspeed);
	game->planey = oldplanex * sin(-rotspeed) + game->planey * cos(-rotspeed);
}

void	rotate_right(t_game *game)
{
	double	rotspeed;
	double	olddirx;
	double	oldplanex;

	rotspeed = 0.05;
	olddirx = game->player->dirx;
	oldplanex = game->planex;
	game->player->dirx = olddirx * cos(rotspeed)
		- game->player->diry * sin(rotspeed);
	game->player->diry = olddirx * sin(rotspeed)
		+ game->player->diry * cos(rotspeed);
	game->planex = game->planex * cos(rotspeed) - game->planey * sin(rotspeed);
	game->planey = oldplanex * sin(rotspeed) + game->planey * cos(rotspeed);
}

void	strafe_left(t_game *game)
{
	double	movespeed;
	double	newx;
	double	newy;

	movespeed = 0.05;
	newx = game->player->x - game->planex * movespeed;
	newy = game->player->y - game->planey * movespeed;
	if (game->info->map[(int)game->player->y][(int)newx] != '1')
		game->player->x = newx;
	if (game->info->map[(int)newy][(int)game->player->x] != '1')
		game->player->y = newy;
}

void	strafe_right(t_game *game)
{
	double	movespeed;
	double	newx;
	double	newy;

	movespeed = 0.05;
	newx = game->player->x + game->planex * movespeed;
	newy = game->player->y + game->planey * movespeed;
	if (game->info->map[(int)game->player->y][(int)newx] != '1')
		game->player->x = newx;
	if (game->info->map[(int)newy][(int)game->player->x] != '1')
		game->player->y = newy;
}
