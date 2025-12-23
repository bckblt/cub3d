/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:31:40 by bakarabu          #+#    #+#             */
/*   Updated: 2025/12/23 17:01:35 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map_chk	*info;
	t_game		*game;

	if (ac != 2)
	{
		printf("Error\nPlease use this format : ./cub3D map.cub\n");
		exit(1);
	}
	info = parse(av[1]);
	if (!info)
		exit (1);
	game = ft_calloc(sizeof(t_game), 1);
	info->max_x = 1920;
	info->max_y = 1080;
	game_engine(game, info);
	exit(0);
}
