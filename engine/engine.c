/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:22:42 by bakarabu          #+#    #+#             */
/*   Updated: 2025/12/23 17:43:53 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (!g)
		return (0);
	if (g->keys)
	{
		if (g->keys->w)
			move_forward(g);
		if (g->keys->s)
			move_backward(g);
		if (g->keys->a)
			strafe_left(g);
		if (g->keys->d)
			strafe_right(g);
		if (g->keys->left)
			rotate_left(g);
		if (g->keys->right)
			rotate_right(g);
	}
	render_frame(g, 0);
	return (0);
}

int	key_press(int key, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (!g)
		return (0);
	if (key == 53 || key == 65307)
		exit_game(g);
	if (!g->keys)
		return (0);
	if (key == 13 || key == 126 || key == 119 || key == 65362)
		g->keys->w = 1;
	if (key == 1 || key == 125 || key == 115 || key == 65364)
		g->keys->s = 1;
	if (key == 0 || key == 97)
		g->keys->a = 1;
	if (key == 2 || key == 100)
		g->keys->d = 1;
	if (key == 123 || key == 65361)
		g->keys->left = 1;
	if (key == 124 || key == 65363)
		g->keys->right = 1;
	return (0);
}

int	key_release(int key, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (!g || !g->keys)
		return (0);
	if (key == 13 || key == 126 || key == 119 || key == 65362)
		g->keys->w = 0;
	if (key == 1 || key == 125 || key == 115 || key == 65364)
		g->keys->s = 0;
	if (key == 0 || key == 97)
		g->keys->a = 0;
	if (key == 2 || key == 100)
		g->keys->d = 0;
	if (key == 123 || key == 65361)
		g->keys->left = 0;
	if (key == 124 || key == 65363)
		g->keys->right = 0;
	return (0);
}

void	game_engine(t_game *game, t_map_chk *info)
{
	game->info = info;
	game->player = (t_player *)ft_calloc(sizeof(t_player), 1);
	game->keys = (t_keys *)ft_calloc(sizeof(t_keys), 1);
	game->init = mlx_init();
	if (!game->player || !game->keys || !game || !info || !game->init)
		exit_game(game);
	game->win = mlx_new_window(game->init, info->max_x, info->max_y, "cub3d");
	if (!game->win)
		exit_game(game);
	game->img = mlx_new_image(game->init, info->max_x, info->max_y);
	if (!game->img)
		exit_game(game);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	load_textures(game);
	init_player(game);
	render_frame(game, 0);
	mlx_hook(game->win, 17, 0, exit_game, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->init, game_loop, game);
	mlx_loop(game->init);
}
