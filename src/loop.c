/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:12:36 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/10 15:54:18 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	quit_game(t_display *display)
{
	free_display(display);
	exit (EXIT_SUCCESS);
}

int	ft_key_hook(int key, t_display *display)
{
	double	oldDir;
	double	oldPlaneX;

	if (key == ESCAPE)
		quit_game(display);
	else if (key == TURN_RIGHT)
	{
		oldDir = display->map->player->direction->x;
		display->map->player->direction->x = display->map->player->direction->x * cos(-ROTATION_SPEED) - display->map->player->direction->y * sin(-ROTATION_SPEED);
		display->map->player->direction->y = oldDir * sin(-ROTATION_SPEED) + display->map->player->direction->y * cos(-ROTATION_SPEED);
		oldPlaneX = display->map->player->plane->x;
		display->map->player->plane->x = display->map->player->plane->x * cos(-ROTATION_SPEED) - display->map->player->plane->y * sin(-ROTATION_SPEED);
		display->map->player->plane->y = oldPlaneX * sin(-ROTATION_SPEED) + display->map->player->plane->y * cos(-ROTATION_SPEED);
	}
	else if (key == TURN_LEFT)
	{
		oldDir = display->map->player->direction->x;
		display->map->player->direction->x = display->map->player->direction->x * cos(ROTATION_SPEED) - display->map->player->direction->y * sin(ROTATION_SPEED);
		display->map->player->direction->y = oldDir * sin(ROTATION_SPEED) + display->map->player->direction->y * cos(ROTATION_SPEED);
		oldPlaneX = display->map->player->plane->x;
		display->map->player->plane->x = display->map->player->plane->x * cos(ROTATION_SPEED) - display->map->player->plane->y * sin(ROTATION_SPEED);
		display->map->player->plane->y = oldPlaneX * sin(ROTATION_SPEED) + display->map->player->plane->y * cos(ROTATION_SPEED);
	}
	return (0);
}

int	ft_mlx_hook(t_display *display)
{
	free_display(display);
	exit (EXIT_SUCCESS);
	return (0);
}

int	ft_loop_hook(t_display *display)
{
	display->new_img = init_image(display);
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
