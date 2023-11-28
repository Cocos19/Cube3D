/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:12:36 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/28 15:32:10 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_mlx_hook(t_display *display)
{
	free_display(display);
	exit (EXIT_SUCCESS);
	return (0);
}

void	update_sprite_texture(t_display *display, int *loop_counter)
{
	if (*loop_counter == 5)
		display->map->sprite_texture = display->map->sprite_2;
	else if (*loop_counter == 10)
		display->map->sprite_texture = display->map->sprite_3;
	else if (*loop_counter == 15)
	{
		*loop_counter = 0;
		display->map->sprite_texture = display->map->sprite_1;
	}
}

int	ft_loop_hook(t_display *display)
{
	static int	loop_counter = 0;

	display->new_img = init_screen_image(display);
	move_player(display);
	render_image(display->new_img, display);
	mlx_clear_window(display->mlx, display->win);
	if (display->old_img)
	{
		mlx_destroy_image(display->mlx, display->old_img->mlx_img);
		free(display->old_img);
		display->old_img = display->new_img;
	}
	else
		display->old_img = display->new_img;
	mlx_put_image_to_window(display->mlx, display->win,
		display->old_img->mlx_img, 0, 0);
	++loop_counter;
	update_sprite_texture(display, &loop_counter);
	return (0);
}
