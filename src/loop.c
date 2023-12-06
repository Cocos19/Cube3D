/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:12:36 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/06 12:58:07 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	update_sprite_texture(t_display *display, int *loop_counter);

int	ft_loop_hook(t_display *display)
{
	static int	loop_counter = 0;

	move_player(display);
	render_image(display->screen_img, display);
	mlx_clear_window(display->mlx, display->win);
	mlx_put_image_to_window(display->mlx, display->win,
		display->screen_img->mlx_img, 0, 0);
	++loop_counter;
	update_sprite_texture(display, &loop_counter);
	return (0);
}

static void	update_sprite_texture(t_display *display, int *loop_counter)
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

int	ft_mlx_hook(void)
{
	exit (EXIT_SUCCESS);
}
