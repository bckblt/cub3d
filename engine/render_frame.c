/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:05:23 by bakarabu          #+#    #+#             */
/*   Updated: 2025/12/23 14:37:57 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_distance(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->mapx - player->x
				+ (1 - ray->stepx) / 2) / ray->raydirx;
	else
		ray->perpwalldist = (ray->mapy - player->y
				+ (1 - ray->stepy) / 2) / ray->raydiry;
}

static void	calculate_step_and_side(t_game *game, t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (game->player->x - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - game->player->x) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (game->player->y - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - game->player->y) * ray->deltadisty;
	}
}

void	cast_single_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)game->info->max_x - 1;
	ray->raydirx = game->player->dirx + game->planex * camera_x;
	ray->raydiry = game->player->diry + game->planey * camera_x;
	ray->mapx = (int)game->player->x;
	ray->mapy = (int)game->player->y;
	if (ray->raydirx == 0)
		ray->deltadistx = 1e30;
	else
		ray->deltadistx = fabs(1 / ray->raydirx);
	if (ray->raydiry == 0)
		ray->deltadisty = 1e30;
	else
		ray->deltadisty = fabs(1 / ray->raydiry);
	calculate_step_and_side(game, ray);
	ray->hit = 0;
	perform_dda(ray, game->info);
	calculate_wall_distance(ray, game->player);
	game->line_h = (int)(game->info->max_y / ray->perpwalldist);
}

static void	calculate_and_draw(t_game *game, t_ray *ray, t_texture *tex, int x)
{
	double	wall_hit;
	int		tex_x;

	if (ray->side == 0)
		wall_hit = game->player->y + ray->perpwalldist * ray->raydiry;
	else
		wall_hit = game->player->x + ray->perpwalldist * ray->raydirx;
	wall_hit -= floor(wall_hit);
	tex_x = (int)(wall_hit * (double)tex->width);
	if (ray->side == 0 && ray->raydirx < 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->raydiry > 0)
		tex_x = tex->width - tex_x - 1;
	draw_textured_column(game, x, tex, tex_x);
}

void	render_frame(t_game *game, int x)
{
	t_ray		ray;
	t_texture	*tex;

	while (x++ < game->info->max_x)
	{
		cast_single_ray(game, &ray, x);
		if (ray.side == 1)
		{
			if (ray.stepy > 0)
				tex = &game->tex_so;
			else
				tex = &game->tex_no;
		}
		else
		{
			if (ray.stepx > 0)
				tex = &game->tex_ea;
			else
				tex = &game->tex_we;
		}
		calculate_and_draw(game, &ray, tex, x);
	}
	mlx_put_image_to_window(game->init, game->win, game->img, 0, 0);
}
