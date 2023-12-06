/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:31:28 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/06 16:55:44 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
	All the move functions will update the player's position by multiplying the
	direction vector by the move speed
	This function checks if by doing so, the player will enter a wall.
	In this case, the movement on the problematic axis doesnt occur
*/
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
}
