/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:45:45 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/21 18:02:10 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_sprites_distance(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->nbr_sprites)
	{
		map->sprites_array[i]->dist = pow(map->player->position->x
			- map->sprites_array[i]->x, 2) + pow(map->player->position->y
			- map->sprites_array[i]->y, 2);
	}
}

t_sprite **get_sprites_array(t_display *display, t_sprite *sprites_lst)
{
	t_sprite	**result;
	t_sprite	*temp;
	int			i;

	result = malloc(sizeof(t_sprite *) * display->map->nbr_sprites);
	if (!result)
		strerror_and_exit(display, "malloc ordered sprites array");
	i = -1;
	temp = sprites_lst;
	while (temp)
	{
		result[++i] = temp;
		temp = temp->next;
	}
	return (result);
}

void	swap_sprites(t_sprite **sprites_array, int i, int j)
{
	t_sprite	*temp;

	temp = sprites_array[i];
	sprites_array[i] = sprites_array[j];
	sprites_array[j] = temp;
}

int	sort_section(t_sprite **sprites_array, int first, int last)
{
	int			i;
	int			j;
	int			pivot;

	pivot = first;
	i = first;
	j = last;
	while (i < j)
	{
		while (sprites_array[i]->dist <= sprites_array[pivot]->dist && i < last)
			++i;
		while (sprites_array[j]->dist > sprites_array[pivot]->dist)
			--j;
		if (i < j)
			swap_sprites(sprites_array, i, j);
	}
	swap_sprites(sprites_array, pivot, j);
	return (j);
}

void	sort_sprites_array(t_sprite **sprites_array, int first, int last)
{
	int	i;

	if (first < last)
	{
		i = sort_section(sprites_array, first, last);
		sort_sprites_array(sprites_array, first, i - 1);
		sort_sprites_array(sprites_array, i + 1, last);
	}
}

void	rotate_sprite_face_camera(t_player *player, t_sprite *sprite)
{
	double	inverse_camera_matrix_determinant;

	sprite->x_relative = sprite->x - player->position->x;
	sprite->y_relative = sprite->y - player->position->y;
	inverse_camera_matrix_determinant = 1.0
		/ ((player->plane->x * player->direction->y)
		- (player->plane->y * player->direction->x));
	sprite->x_relative = inverse_camera_matrix_determinant
		* ((player->direction->y * sprite->x_relative)
		- (player->direction->x * sprite->y_relative));
	sprite->y_relative = inverse_camera_matrix_determinant
		* ((-1 * player->plane->y * sprite->x_relative)
		+ (player->plane->x * sprite->y_relative));
}

void	get_sprite_drawing_infos(t_sprite *sprite)
{
	sprite->screen_correction = (int)((SCREEN_WIDTH / 2)
		* (1 / sprite->x_relative / sprite->y_relative));
	sprite->width = abs((int)(SCREEN_WIDTH / sprite->x_relative)); //check after in case of problem
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

void	draw_sprite(t_map *map, t_img *screen, t_img *texture, t_sprite *sprite)
{
	int			y;
	int			stripe;
	int			distance;
	t_dot_index	texture_position;

	stripe = sprite->draw_x_start - 1;
	while (++stripe < sprite->dist)
	{
		texture_position.x = (int)(256 * (stripe - (-1 * sprite->width / 2 + sprite->screen_correction)) * TEXTURE_WIDTH / sprite->width) / 256;
		if (sprite->y_relative > 0 && stripe > 0 && stripe < SCREEN_WIDTH && sprite->y_relative < map->player->walls_distance[stripe])
		{
			y = sprite->draw_y_start - 1;
			while (++y < sprite->draw_y_end)
			{
				distance = y * 256 - SCREEN_HEIGHT * 128 + sprite->height * 128;
				texture_position.y = ((distance / TEXTURE_HEIGHT) / sprite->height) / 256;
				put_pixel_on_img(screen, stripe, y, texture->addr[TEXTURE_WIDTH * texture_position.x + texture_position.y]);
				//
			}
		}
	}
}

void	render_sprites(t_map *map, t_img *screen, t_img *texture)
{
	int	i;

	i = -1;
	sort_sprites_array(map->sprites_array, 0, map->nbr_sprites - 1);
	while (++i < map->nbr_sprites)
	{
		rotate_sprite_face_camera(map->player, map->sprites_array[i]);
		get_sprite_drawing_infos(map->sprites_array[i]);
		draw_sprite(map, screen, texture, map->sprites_array[i]);
	}
}
