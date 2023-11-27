/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:45:45 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/27 16:02:52 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_sprite_face_camera(t_player *player, t_sprite *sprite)
{
	double	inverse_camera_matrix_determinant;
	double	sprite_x;
	double	sprite_y;

	sprite_x = sprite->x - player->position->x;
	sprite_y = sprite->y - player->position->y;
	inverse_camera_matrix_determinant = 1.0
		/ (player->plane->x * player->direction->y
			- player->direction->x * player->plane->y);
	sprite->x_relative = inverse_camera_matrix_determinant
		* (player->direction->y * sprite_x
			- player->direction->x * sprite_y);
	sprite->y_relative = inverse_camera_matrix_determinant
		* (-1 * player->plane->y * sprite_x
			+ player->plane->x * sprite_y);
}

void	get_sprite_drawing_infos(t_sprite *sprite)
{
	sprite->screen_correction = (int)((SCREEN_WIDTH / 2)
			* (1 + sprite->x_relative / sprite->y_relative));
	sprite->width = abs((int)(SCREEN_HEIGHT / sprite->y_relative));
	sprite->height = abs((int)(SCREEN_HEIGHT / sprite->y_relative));
	sprite->draw_x_start = -1 * sprite->width / 2 + sprite->screen_correction;
	if (sprite->draw_x_start < 0)
		sprite->draw_x_start = 0;
	sprite->draw_x_end = sprite->width / 2 + sprite->screen_correction;
	if (sprite->draw_x_end >= SCREEN_WIDTH)
		sprite->draw_x_end = SCREEN_WIDTH - 1;
	sprite->draw_y_start = -1 * sprite->height / 2 + SCREEN_HEIGHT / 2;
	if (sprite->draw_y_start < 0)
		sprite->draw_y_start = 0;
	sprite->draw_y_end = sprite->height / 2 + SCREEN_HEIGHT / 2;
	if (sprite->draw_y_end >= SCREEN_HEIGHT)
		sprite->draw_y_end = SCREEN_HEIGHT - 1;
}

int	sprite_is_on_screen(t_map *map, t_sprite *sprite)
{
	if (sprite->y_relative > 0 && sprite->draw_x_start > 0
		&& sprite->draw_x_start < SCREEN_WIDTH && sprite->y_relative
		< map->player->walls_perp_distance[sprite->draw_x_start])
		return (0);
	return (1);
}

void	draw_sprite(t_map *map, t_img *screen, t_img *texture, t_sprite *sprite)
{
	int			y;
	int			distance;
	int			color;
	t_dot_index	sprite_position;

	while (sprite->draw_x_start < sprite->draw_x_end)
	{
		sprite_position.x = (int)((sprite->draw_x_start - (-1
						* sprite->width / 2 + sprite->screen_correction))
				* TEXTURE_WIDTH / sprite->width);
		if (sprite_is_on_screen(map, sprite) == 0)
		{
			y = sprite->draw_y_start - 1;
			while (++y < sprite->draw_y_end)
			{
				distance = y - SCREEN_HEIGHT / 2 + sprite->height / 2;
				sprite_position.y = (distance * SPRITE_HEIGHT / sprite->height);
				color = get_pixel_color(texture, &sprite_position);
				if ((color & 0x00FFFFFF) != 0)
					put_pixel_on_img(screen, sprite->draw_x_start, y, color);
			}
		}
		++sprite->draw_x_start;
	}
}

void	render_sprites(t_map *map, t_img *screen, t_img *texture)
{
	int	i;

	i = map->nbr_sprites;
	get_sprites_distance(map);
	sort_sprites_array(map->sprites_array, 0, map->nbr_sprites - 1);
	while (--i >= 0)
	{
		rotate_sprite_face_camera(map->player, map->sprites_array[i]);
		get_sprite_drawing_infos(map->sprites_array[i]);
		draw_sprite(map, screen, texture, map->sprites_array[i]);
	}
}
