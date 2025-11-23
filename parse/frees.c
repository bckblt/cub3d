/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 04:53:45 by hadalici          #+#    #+#             */
/*   Updated: 2025/11/23 05:46:15 by hadalici         ###   ########.fr       */
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
		free(info->ET);
		free(info->WT);
		free(info->ST);
		free(info->NT);
		free(info);
	}
}
