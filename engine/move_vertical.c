/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:40:03 by bakarabu          #+#    #+#             */
/*   Updated: 2025/12/21 19:50:49 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	movespeed;
	double	padding;
	double	newx;
	double	newy;

	movespeed = 0.1;
	padding = 0.01;
	newx = game->player->x + game->player->dirx * movespeed;
	newy = game->player->y + game->player->diry * movespeed;
	if (!is_wall((newx + game->player->dirx * padding), game->player->y, game))
		game->player->x = newx;
	if (!is_wall(game->player->x, newy + game->player->diry * padding, game))
		game->player->y = newy;
}

void	move_backward(t_game *game)
{
	double	movespeed;
	double	newx;
	double	newy;

	movespeed = 0.1;
	newx = game->player->x - game->player->dirx * movespeed;
	newy = game->player->y - game->player->diry * movespeed;
	if (game->info->map[(int)game->player->y][(int)newx] != '1')
		game->player->x = newx;
	if (game->info->map[(int)newy][(int)game->player->x] != '1')
		game->player->y = newy;
}
