/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:30:49 by bakarabu          #+#    #+#             */
/*   Updated: 2025/12/23 16:57:18 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_game *game, t_texture *tex, const char *path)
{
	tex->img = mlx_xpm_file_to_image(game->init, (char *)path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\ntexture_load_failed: %s\n", path);
		exit_game(game);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
	{
		printf("Error\ntexture_data_addr_failed: %s\n", path);
		exit_game(game);
	}
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->tex_no, game->info->nt);
	load_texture(game, &game->tex_so, game->info->st);
	load_texture(game, &game->tex_we, game->info->wt);
	load_texture(game, &game->tex_ea, game->info->et);
}
