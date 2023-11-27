/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:31:28 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/27 16:05:07 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*All the move function will update the player position by multiplying the
direction vector by the move speed
This function check if by doing so, the player will enter a wall.
In this case, the movement on the problematic axis doesnt occur*/

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

void	straf_left(t_display *display)
{
	if (display->map->tiles[(int)(display->map->player->position->x
			- display->map->player->direction->y * MOVE_SPEED)]
			[(int)display->map->player->position->y] == '0')
	{
		display->map->player->position->x
			-= display->map->player->direction->y * MOVE_SPEED;
		display->map->player->y
			-= display->map->player->direction->y * MOVE_SPEED;
	}
	if (display->map->tiles[(int)display->map->player->position->x]
		[(int)(display->map->player->position->y
			+ display->map->player->direction->x * MOVE_SPEED)] == '0')
	{
		display->map->player->position->y
			+= display->map->player->direction->x * MOVE_SPEED;
		display->map->player->x
			+= display->map->player->direction->x * MOVE_SPEED;
	}
}

void	straf_right(t_display *display)
{
	if (display->map->tiles[(int)(display->map->player->position->x
			+ display->map->player->direction->y * MOVE_SPEED)]
			[(int)display->map->player->position->y] == '0')
	{
		display->map->player->position->x
			+= display->map->player->direction->y * MOVE_SPEED;
		display->map->player->y
			+= display->map->player->direction->y * MOVE_SPEED;
	}
	if (display->map->tiles[(int)display->map->player->position->x]
		[(int)(display->map->player->position->y
			- display->map->player->direction->x * MOVE_SPEED)] == '0')
	{
		display->map->player->position->y
			-= display->map->player->direction->x * MOVE_SPEED;
		display->map->player->x
			-= display->map->player->direction->x * MOVE_SPEED;
	}
}

/*This function will check the player status.
If the moving or the strafing status where modified by the hooks,
this function will update the player informations.
Then, if the mouse mode is enabled, it will calculate the distance between
the center of the windows and mouse movements
in order to update player position too*/

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
