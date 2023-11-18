/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:31:28 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/18 16:45:01 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*All the move function will update the player position by multiplying the direction vector by the move speed
This function check if by doing so, the player will enter a wall. In this case, the movement on the problematic axis doesnt occur*/

void	move_forward(t_display *display)
{
	if (display->map->tiles[(int)(display->map->player->position->x
			+ display->map->player->direction->x * MOVE_SPEED)]
			[(int)display->map->player->position->y] == '0')
	{
		display->map->player->position->x
			+= display->map->player->direction->x * MOVE_SPEED;
		display->map->player->y
			+= display->map->player->direction->x * MOVE_SPEED;
	}
	if (display->map->tiles[(int)display->map->player->position->x]
		[(int)(display->map->player->position->y
			+ display->map->player->direction->y * MOVE_SPEED)] == '0')
	{
		display->map->player->position->y
			+= display->map->player->direction->y * MOVE_SPEED;
		display->map->player->x
			+= display->map->player->direction->y * MOVE_SPEED;
	}
}

void	move_backward(t_display *display)
{
	if (display->map->tiles[(int)(display->map->player->position->x
			- display->map->player->direction->x * MOVE_SPEED)]
			[(int)display->map->player->position->y] == '0')
	{
		display->map->player->position->x
			-= display->map->player->direction->x * MOVE_SPEED;
		display->map->player->y
			-= display->map->player->direction->x * MOVE_SPEED;
	}
	if (display->map->tiles[(int)display->map->player->position->x]
		[(int)(display->map->player->position->y
			- display->map->player->direction->y * MOVE_SPEED)] == '0')
	{
		display->map->player->position->y
			-= display->map->player->direction->y * MOVE_SPEED;
		display->map->player->x
			-= display->map->player->direction->y * MOVE_SPEED;
	}
}

/*This functions perform a rotation of the direction and the plane vector on the players infos
Since the raycast algorythm use the direction and the plane in order to cast the rays, the player view is update in the screen rendering*/

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

/*This function will check the player status.
If the moving or the strafing status where modified by the hooks, this function will update the player informations.
Then, if the mouse mode is enabled, it will calculate the distance between the center of the windows and mouse movements in order to update player position too*/

void	move_player(t_display *display)
{
	int	x = -1;
	int	y = -1;

	mlx_mouse_get_pos(display->win, &x, &y);
	if (display->map->player->is_moving == MOVE_FORWARD)
		move_forward(display);
	else if (display->map->player->is_moving == MOVE_BACKWARD)
		move_backward(display);
	if (display->map->player->is_strafing == TURN_RIGHT)
		turn_right(display);
	else if (display->map->player->is_strafing == TURN_LEFT)
		turn_left(display);
	if (x > 0 && x < SCREEN_WIDTH && y > 0 && y < SCREEN_HEIGHT && display->map->player->is_strafing == -1 && display->mouse_enabled == 1)
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
