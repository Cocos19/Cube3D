/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:31:28 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/02 12:28:54 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*All the move function will update the player position by multiplying the
direction vector by the move speed
This function check if by doing so, the player will enter a wall.
In this case, the movement on the problematic axis doesnt occur*/

/*This function will check the player status.
If the moving or the strafing status where modified by the hooks,
this function will update the player informations.
Then, if the mouse mode is enabled, it will calculate the distance between
the center of the windows and mouse movements
in order to update player position too*/

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

void	move_player(t_display *display)
{
	if (display->map->player->is_moving == MOVE_FORWARD)
		move_forward(display);
	else if (display->map->player->is_moving == MOVE_BACKWARD)
		move_backward(display);
	else if (display->map->player->is_strafing == STRAF_LEFT)
		straf_left(display);
	else if (display->map->player->is_strafing == STRAF_RIGHT)
		straf_right(display);
	if (display->map->player->is_turning == TURN_RIGHT)
		turn_right(display);
	else if (display->map->player->is_turning == TURN_LEFT)
		turn_left(display);
	execute_mouse_moves(display);
}
