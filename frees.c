/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 04:53:45 by hadalici          #+#    #+#             */
/*   Updated: 2025/12/21 20:29:39 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_frees(t_map_chk *info, int key)
{
	if (key == 0)
	{
		free_dp(info->full_file);
		free_dp(info->map);
		free(info);
	}
	else if (key == 2)
	{
		free_dp(info->full_file);
		free_dp(info->map);
		free(info->et);
		free(info->wt);
		free(info->st);
		free(info->nt);
		free(info);
	}
}

void	free_dp(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_img(t_game *game)
{
	if (!game)
		exit(0);
	if (game->init)
	{
		if (game->tex_no.img)
			mlx_destroy_image(game->init, game->tex_no.img);
		if (game->tex_so.img)
			mlx_destroy_image(game->init, game->tex_so.img);
		if (game->tex_we.img)
			mlx_destroy_image(game->init, game->tex_we.img);
		if (game->tex_ea.img)
			mlx_destroy_image(game->init, game->tex_ea.img);
		if (game->img)
			mlx_destroy_image(game->init, game->img);
		if (game->win)
			mlx_destroy_window(game->init, game->win);
		mlx_destroy_display(game->init);
		free(game->init);
	}
	if (game->player)
		free(game->player);
	if (game->keys)
		free(game->keys);
}

int	exit_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_img(game);
	if (game->info)
	{
		if (game->info->map)
			free_dp(game->info->map);
		if (game->info->full_file)
			free_dp(game->info->full_file);
		if (game->info->nt)
			free(game->info->nt);
		if (game->info->st)
			free(game->info->st);
		if (game->info->wt)
			free(game->info->wt);
		if (game->info->et)
			free(game->info->et);
		free(game->info);
	}
	free (game);
	exit (0);
	return (0);
}
