/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:18:58 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/28 14:10:02 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_plane_infos(t_player *player, char c)
{
	if (c == 'N')
	{
		player->plane->x = 0.0;
		player->plane->y = 0.66;
	}
	else if (c == 'E')
	{
		player->plane->x = 0.66;
		player->plane->y = 0.0;
	}
	else if (c == 'W')
	{
		player->plane->x = -0.66;
		player->plane->y = 0.0;
	}
	else if (c == 'S')
	{
		player->plane->x = 0.0;
		player->plane->y = -0.66;
	}
}

void	init_direction_infos(t_player *player, char c)
{
	if (c == 'N')
	{
		player->direction->x = -1.0;
		player->direction->y = 0.0;
	}
	else if (c == 'E')
	{
		player->direction->x = 0.0;
		player->direction->y = 1.0;
	}
	else if (c == 'W')
	{
		player->direction->x = 0.0;
		player->direction->y = -1.0;
	}
	else if (c == 'S')
	{
		player->direction->x = 1.0;
		player->direction->y = 0.0;
	}
}

void	malloc_player_datas_structures(t_display *display)
{
	display->map->player->direction = malloc(sizeof(t_vector));
	if (!display->map->player->direction)
		strerror_and_exit(display, "malloc on player direction");
	display->map->player->plane = malloc(sizeof(t_vector));
	if (!display->map->player->plane)
		strerror_and_exit(display, "malloc on player plane");
	display->map->player->position = malloc(sizeof(t_dot));
	if (!display->map->player->position)
		strerror_and_exit(display, "malloc on player position");
	display->map->player->walls_perp_distance
		= malloc(sizeof(double) * SCREEN_WIDTH);
	if (!display->map->player->walls_perp_distance)
		strerror_and_exit(display, "malloc on walls distance");
}

int	init_player_infos(t_display *display, char c, int i, int j)
{
	malloc_player_datas_structures(display);
	display->map->player->position->x = -1;
	if ((c == 'N' || c == 'S' || c == 'W' || c == 'E')
		&& display->map->player->exist != 0)
		map_error_and_exit(display, "More than one player on map");
	display->map->player->exist = 1;
	init_direction_infos(display->map->player, c);
	init_plane_infos(display->map->player, c);
	display->map->player->x = j + 0.5;
	display->map->player->y = i + 0.5;
	display->map->player->position->x = i + 0.5;
	display->map->player->position->y = j + 0.5;
	display->map->player->is_moving = -1;
	display->map->player->is_turning = -1;
	display->map->player->is_strafing = -1;
	display->map->tiles[i][j] = '0';
	return (0);
}
