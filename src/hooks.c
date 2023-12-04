/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:30:51 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/04 18:44:14 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_key_press_hook(int key, t_display *display)
{
	if (key == ESCAPE)
		exit (EXIT_SUCCESS);
	else if (key == MOVE_FORWARD)
		display->map->player->is_moving = MOVE_FORWARD;
	else if (key == MOVE_BACKWARD)
		display->map->player->is_moving = MOVE_BACKWARD;
	else if (key == TURN_RIGHT)
		display->map->player->is_turning = TURN_RIGHT;
	else if (key == TURN_LEFT)
		display->map->player->is_turning = TURN_LEFT;
	else if (key == STRAF_LEFT)
		display->map->player->is_strafing = STRAF_LEFT;
	else if (key == STRAF_RIGHT)
		display->map->player->is_strafing = STRAF_RIGHT;
	else if (key == INTERACT)
		open_or_close_door(display->map);
	return (0);
}

void	execute_rotation(int key, t_display *display)
{
	if (key == STRAF_LEFT)
	{
		if (display->map->player->is_strafing == STRAF_LEFT)
			display->map->player->is_strafing = -1;
	}
	else if (key == STRAF_RIGHT)
	{
		if (display->map->player->is_strafing == STRAF_RIGHT)
			display->map->player->is_strafing = -1;
	}
}

int	ft_key_release_hook(int key, t_display *display)
{
	if (key == ESCAPE)
		exit (EXIT_SUCCESS);
	else if (key == MOVE_FORWARD)
	{
		if (display->map->player->is_moving == MOVE_FORWARD)
			display->map->player->is_moving = -1;
	}
	else if (key == MOVE_BACKWARD)
	{
		if (display->map->player->is_moving == MOVE_BACKWARD)
			display->map->player->is_moving = -1;
	}
	else if (key == TURN_RIGHT)
	{
		if (display->map->player->is_turning == TURN_RIGHT)
			display->map->player->is_turning = -1;
	}
	else if (key == TURN_LEFT)
	{
		if (display->map->player->is_turning == TURN_LEFT)
			display->map->player->is_turning = -1;
	}
	execute_rotation(key, display);
	return (0);
}

int	ft_mouse_hook(int key, t_display *display)
{
	if (key == 1)
	{
		if (display->mouse_enabled == 0)
		{
			mlx_mouse_hide();
			display->mouse_x = MOUSE_ORIGIN_X;
			display->mouse_enabled = 1;
		}
		else
		{
			mlx_mouse_show();
			display->mouse_enabled = 0;
		}
	}
	return (0);
}
