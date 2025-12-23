/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:45:10 by bakarabu          #+#    #+#             */
/*   Updated: 2025/12/21 20:28:24 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_game *game, int x, int draw_start)
{
	int		y;
	char	*dst;

	y = 0;
	while (y < draw_start)
	{
		dst = game->addr + (y * game->line_length
				+ x * (game->bits_per_pixel / 8));
		*(unsigned int *)dst = (unsigned int)game->info->c_c;
		y++;
	}
}

void	draw_floor(t_game *game, int x, int draw_end)
{
	int		y;
	char	*dst;
	int		screen_h;

	screen_h = game->info->max_y;
	y = draw_end + 1;
	while (y < screen_h)
	{
		dst = game->addr + (y * game->line_length
				+ x * (game->bits_per_pixel / 8));
		*(unsigned int *)dst = (unsigned int)game->info->f_c;
		y++;
	}
}

void	draw_wall_strip(t_game *game, int x, int *vars, t_texture *tex)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;

	step = 1.0 * tex->height / vars[2];
	tex_pos = (vars[0] - game->info->max_y / 2 + vars[2] / 2) * step;
	y = vars[0];
	while (y <= vars[1])
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		*(unsigned int *)(game->addr
				+ (y * game->line_length + x * (game->bits_per_pixel / 8)))
			= *(unsigned int *)(tex->addr
				+ (tex_y * tex->line_length + vars[3] * (tex->bpp / 8)));
		y++;
	}
}

void	draw_textured_column(t_game *game, int x, t_texture *tex, int texX)
{
	int	vars[4];
	int	screen_h;

	if (!tex || !tex->addr)
		return ;
	screen_h = game->info->max_y;
	vars[2] = game->line_h;
	vars[0] = -game->line_h / 2 + screen_h / 2;
	if (vars[0] < 0)
		vars[0] = 0;
	vars[1] = game->line_h / 2 + screen_h / 2;
	if (vars[1] >= screen_h)
		vars[1] = screen_h - 1;
	vars[3] = texX;
	draw_ceiling(game, x, vars[0]);
	draw_wall_strip(game, x, vars, tex);
	draw_floor(game, x, vars[1]);
}
