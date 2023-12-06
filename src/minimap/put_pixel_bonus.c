/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:31:03 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/06 20:08:20 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
#include "../../cub3d_bonus.h"

int	pixel_is_in_minimap(double x, double y)
{
	double	distance;
	double	radius;

	radius = 125;
	distance
		= sqrtf(pow(x - (SCREEN_WIDTH - 125), 2) + pow(y - 125, 2)) - radius;
	if (distance <= -3.00000000)
		return (0);
	return (1);
}

int	pixel_is_player(double x, double y)
{
	if (pow(x, 2) + pow(y, 2) < pow(PLAYER_RADIUS, 2))
		return (0);
	return (1);
}

int	pixel_is_out_of_map(t_map *map, int x, int y)
{
	if (x < 0 || y < 0
		|| y > map->map_height || (size_t)x >= ft_strlen(map->tiles[y]))
		return (0);
	return (1);
}

int	pixel_is_in_minimap_border(double x, double y)
{
	double	distance;
	double	radius;

	radius = 125;
	distance
		= sqrtf(pow(x - (SCREEN_WIDTH - 125), 2) + pow(y - 125, 2)) - radius;
	if (distance <= 0.00000000 && !(distance <= -3.00000000))
		return (0);
	return (1);
}

/*
	This function is used pixel by pixel in the minimap rendering.
	For each pixel, this function will check the pixel relative position from
	the player position. Then it will check the tile where the pixel is.
	Except for the field of view of the player,
	there is no calculation to make to get the right color to put.
	In case of a pixel in FOV, we will use a raycast algorithm from the player
	position to the pixel relative position and check if it is behind a wall or not
*/
void	put_pixel_on_minimap(t_img *img, t_map *map, t_dot *pixel)
{
	t_dot	pix_index;
	t_dot	pix_on_minimap;

	pix_on_minimap.x = MINIMAP_CENTER_X - pixel->x;
	pix_on_minimap.y = MINIMAP_CENTER_Y - pixel->y;
	pix_index.x = map->player->position->y - (pix_on_minimap.x / MINIMAP_SCALE);
	pix_index.y = map->player->position->x - (pix_on_minimap.y / MINIMAP_SCALE);
	if (pixel_is_player(pix_on_minimap.x, pix_on_minimap.y) == 0)
		put_pixel_on_img(img, pixel->x, pixel->y, map->minimap_player_color);
	else if (pixel_is_out_of_map(map, (int)pix_index.x, (int)pix_index.y) == 0)
		put_pixel_on_img(img, pixel->x, pixel->y, map->minimap_empty_color);
	else if (map->tiles[(int)pix_index.y][(int)pix_index.x] == ' ')
		put_pixel_on_img(img, pixel->x, pixel->y, map->minimap_empty_color);
	else if (map->tiles[(int)pix_index.y][(int)pix_index.x] == '0')
		put_empty_pix(img, map, pixel, &pix_on_minimap);
	else if (map->tiles[(int)pix_index.y][(int)pix_index.x] == '1')
		put_pixel_on_img(img, pixel->x, pixel->y, map->minimap_walls_color);
	else if (map->tiles[(int)pix_index.y][(int)pix_index.x] == 'D')
		put_pixel_on_img(img, pixel->x, pixel->y, map->minimap_door_color);
	else if (map->tiles[(int)pix_index.y][(int)pix_index.x] == 'P')
		put_pixel_on_img(img, pixel->x, pixel->y, map->minimap_pillar_color);
}
