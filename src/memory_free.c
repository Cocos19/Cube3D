/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:30:11 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/04 10:47:59 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_player(t_player *player)
{
	if (player->position)
		free(player->position);
	if (player->direction)
		free(player->direction);
	if (player->plane)
		free(player->plane);
	if (player)
		free(player);
}

void	free_map(t_display *display)
{
	free_map_images(display);
	if (display->map->player)
		free_player(display->map->player);
	if (display->map->tiles)
		ft_free_str_array(display->map->tiles);
	if (display->map->sprites_array)
		free_sprite_array(display->map);
}

void	free_display(t_display *display)
{
	if (display->mlx && display->win)
		mlx_clear_window(display->mlx, display->win);
	if (display->map)
		free_map(display);
	if (display->win)
		mlx_destroy_window(display->mlx, display->win);
	if (display->screen_img)
		free_image(display, display->screen_img);
}

void	map_error_and_exit(t_display *display, char *error_msg)
{
	if (display)
		free_display(display);
	ft_printf("Error\n%s\n", error_msg);
	exit (EXIT_FAILURE);
}

void	strerror_and_exit(t_display *display, char *error_msg)
{
	if (display)
		free_display(display);
	ft_printf("Error when %s: %s\n", error_msg, strerror(errno));
	system("leaks cub3D");
	exit (EXIT_FAILURE);
}
