/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:29:48 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/04 10:22:40 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_image(t_display *display, t_img *image)
{
	if (image->mlx_img)
		mlx_destroy_image(display->mlx, image->mlx_img);
	if (image)
		free(image);
}

void	free_map_images(t_display *display)
{
	if (display->map->sprite_1)
		free_image(display, display->map->sprite_1);
	if (display->map->sprite_2)
		free_image(display, display->map->sprite_2);
	if (display->map->sprite_3)
		free_image(display, display->map->sprite_3);
	if (display->map->north_texture)
		free_image(display, display->map->north_texture);
	if (display->map->south_texture)
		free_image(display, display->map->south_texture);
	if (display->map->west_texture)
		free_image(display, display->map->west_texture);
	if (display->map->east_texture)
		free_image(display, display->map->east_texture);
	if (display->map->door_texture)
		free_image(display, display->map->door_texture);
}

void	free_sprite_array(t_map *map)
{
	int	i;

	i = map->nbr_sprites - 2;
	while (++i < map->nbr_sprites)
	{
		free(map->sprites_array[i]);
	}
	free(map->sprites_array);
}
