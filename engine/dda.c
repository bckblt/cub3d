/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:49:10 by bakarabu          #+#    #+#             */
/*   Updated: 2025/12/21 20:28:14 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_utils(t_ray *ray, t_map_chk *info, int mapH)
{
	int	row_len;

	if (ray->mapy < 0 || ray->mapy >= mapH)
	{
		ray->hit = 1;
		return ;
	}
	row_len = (int)ft_strlen(info->map[ray->mapy]);
	if (ray->mapx < 0 || ray->mapx >= row_len)
	{
		ray->hit = 1;
		return ;
	}
	if (info->map[ray->mapy][ray->mapx] == '1')
		ray->hit = 1;
}

void	perform_dda(t_ray *ray, t_map_chk *info)
{
	int	map_h;

	map_h = 0;
	while (info->map[map_h])
		map_h++;
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		dda_utils(ray, info, map_h);
	}
}
