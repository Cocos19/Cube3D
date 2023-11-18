/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:12:36 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/18 16:25:53 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	quit_game(t_display *display)
{
	free_display(display);
	exit (EXIT_SUCCESS);
}

int	ft_key_press_hook(int key, t_display *display)
{
	if (key == ESCAPE)
		quit_game(display);
	else if (key == MOVE_FORWARD)
		display->map->player->is_moving = MOVE_FORWARD;
	else if (key == MOVE_BACKWARD)
		display->map->player->is_moving = MOVE_BACKWARD;
	else if (key == TURN_RIGHT)
		display->map->player->is_strafing = TURN_RIGHT;
	else if (key == TURN_LEFT)
		display->map->player->is_strafing = TURN_LEFT;
	else if (key == INTERACT)
		open_door(display->map);
	return (0);
}

int	ft_key_release_hook(int key, t_display *display)
{
	if (key == ESCAPE)
		quit_game(display);
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
		if (display->map->player->is_strafing == TURN_RIGHT)
			display->map->player->is_strafing = -1;
	}
	else if (key == TURN_LEFT)
	{
		if (display->map->player->is_strafing == TURN_LEFT)
			display->map->player->is_strafing = -1;
	}
	return (0);
}

int	ft_mlx_hook(t_display *display)
{
	free_display(display);
	exit (EXIT_SUCCESS);
	return (0);
}

int	ft_mouse_hook(int key, int x, int y, t_display *display)
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
	(void) x;
	(void) y;
	return (0);
}

int	ft_loop_hook(t_display *display)
{
	display->new_img = init_image(display);
	move_player(display);
	render_image(display->new_img, display);
	mlx_clear_window(display->mlx, display->win);
	if (display->old_img)
	{
		mlx_destroy_image(display->mlx, display->old_img->mlx_img);
		display->old_img = display->new_img;
	}
	else
		display->old_img = display->new_img;
	mlx_put_image_to_window(display->mlx, display->win,
		display->old_img->mlx_img, 0, 0);
	return (0);
}
