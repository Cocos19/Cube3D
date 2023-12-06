/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:13:12 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/06 20:09:13 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
	This functions performs a rotation of the direction and the plane vector
	on the players infos.
	Since the raycast algorithm uses the direction and the plane in order to cast
	the rays, the player's view is updated in the screen rendering
*/
void	turn_right(t_display *display)
{
	double	old_dir;
	double	old_plane_x;

	old_dir = display->map->player->direction->x;
	display->map->player->direction->x = display->map->player->direction->x
		* cos(-ROTATION_SPEED) - display->map->player->direction->y
		* sin(-ROTATION_SPEED);
	display->map->player->direction->y = old_dir * sin(-ROTATION_SPEED)
		+ display->map->player->direction->y * cos(-ROTATION_SPEED);
	old_plane_x = display->map->player->plane->x;
	display->map->player->plane->x = display->map->player->plane->x
		* cos(-ROTATION_SPEED) - display->map->player->plane->y
		* sin(-ROTATION_SPEED);
	display->map->player->plane->y = old_plane_x * sin(-ROTATION_SPEED)
		+ display->map->player->plane->y * cos(-ROTATION_SPEED);
}

void	turn_left(t_display *display)
{
	double	old_dir;
	double	old_plane_x;

	old_dir = display->map->player->direction->x;
	display->map->player->direction->x = display->map->player->direction->x
		* cos(ROTATION_SPEED) - display->map->player->direction->y
		* sin(ROTATION_SPEED);
	display->map->player->direction->y = old_dir * sin(ROTATION_SPEED)
		+ display->map->player->direction->y * cos(ROTATION_SPEED);
	old_plane_x = display->map->player->plane->x;
	display->map->player->plane->x = display->map->player->plane->x
		* cos(ROTATION_SPEED) - display->map->player->plane->y
		* sin(ROTATION_SPEED);
	display->map->player->plane->y = old_plane_x * sin(ROTATION_SPEED)
		+ display->map->player->plane->y * cos(ROTATION_SPEED);
}
