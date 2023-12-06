/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:13:26 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/06 13:22:26 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
#include "../../cub3d_bonus.h"

int	radian_is_in_fov_range(double player_rad, double pix_rad)
{
	double	difference;

	if ((player_rad <= 0 && pix_rad <= 0) || (player_rad >= 0 && pix_rad >= 0))
	{
		if (fabs(player_rad) >= fabs(pix_rad))
			difference = fabs(player_rad) - fabs(pix_rad);
		else
			difference = fabs(pix_rad) - fabs(player_rad);
	}
	else
	{
		if ((fabs(player_rad) > PI - HALF_FOV && fabs(pix_rad) > PI - HALF_FOV))
			difference = PI - fabs(player_rad) + PI - fabs(pix_rad);
		else if ((fabs(player_rad) < HALF_FOV && fabs(pix_rad) < HALF_FOV))
			difference = fabs(player_rad) + fabs(pix_rad);
		else
			return (1);
	}
	if (difference < HALF_FOV)
		return (0);
	return (1);
}

double	get_player_direction_rad(t_vector *direction)
{
	double	radian;

	radian = acos((direction->y * 5)
			/ (sqrtf((powf(direction->y, 2)) + powf(direction->x, 2)) * 5));
	if (direction->x > 0.0)
		radian *= -1;
	if (radian < -1 * (PI / 2))
		return ((PI / 2) + PI - (fabs(radian)));
	else
		return (radian - (PI / 2));
	return (radian);
}

double	get_pixel_rad(t_dot *pixel)
{
	double	radian;

	radian = acos((pixel->y * 5)
			/ (sqrtf((powf(pixel->y, 2)) + powf(pixel->x, 2)) * 5));
	if (pixel->x > 0.0)
		return (radian);
	return (radian * -1);
}

int	pixel_is_in_fov(t_map *map, t_dot *pixel)
{
	t_dot		end_point;

	if (radian_is_in_fov_range(get_player_direction_rad(map->player->direction)
			, get_pixel_rad(pixel)) == 0)
	{
		end_point.x = map->player->position->x - (pixel->y / MINIMAP_SCALE);
		end_point.y = map->player->position->y - (pixel->x / MINIMAP_SCALE);
		return (minimap_raycast(map, &end_point));
	}
	return (1);
}

void	put_empty_pix(t_img *img, t_map *map, t_dot *pixel, t_dot *map_pix)
{
	if (pixel_is_in_fov(map, map_pix) == 0)
		put_pixel_on_img(img, pixel->x, pixel->y, map->minimap_fov_color);
	else
		put_pixel_on_img(img, pixel->x, pixel->y, map->minimap_floor_color);
}
