/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_rotations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:13:12 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/27 16:03:36 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*This functions perform a rotation of the direction and the plane vector
on the players infos
Since the raycast algorythm use the direction and the plane in order to cast
the rays, the player view is update in the screen rendering*/

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

void	execute_mouse_moves(t_display *display)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	mlx_mouse_get_pos(display->win, &x, &y);
	if (x > 0 && x < SCREEN_WIDTH && y > 0 && y < SCREEN_HEIGHT
		&& display->map->player->is_turning == -1
		&& display->mouse_enabled == 1)
	{
		if (MOUSE_ORIGIN_X - x > 0)
		{
			turn_left(display);
			display->mouse_x = x;
		}
		else if (MOUSE_ORIGIN_X - x < 0)
		{
			turn_right(display);
			display->mouse_x = x;
		}
		mlx_mouse_move(display->win, MOUSE_ORIGIN_X, MOUSE_ORIGIN_Y);
	}
}
