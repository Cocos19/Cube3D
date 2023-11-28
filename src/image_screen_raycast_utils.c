/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_screen_raycast_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:37:54 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/28 14:31:44 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_ray *ray, t_map *map, int *x)
{
	double	camera_x;

	camera_x = 2 * *x / (double)(SCREEN_WIDTH) - 1;
	ray->direction.x
		= map->player->direction->x + map->player->plane->x * camera_x;
	ray->direction.y
		= map->player->direction->y + map->player->plane->y * camera_x;
	ray->origin.x = (int)map->player->position->x;
	ray->origin.y = (int)map->player->position->y;
	ray->step_x = 1;
	ray->step_y = 1;
	ray->hit = 0;
	if (ray->direction.x == 0)
		ray->delta_distance.x = 1e30;
	else
		ray->delta_distance.x = fabs(1 / ray->direction.x);
	if (ray->direction.y == 0)
		ray->delta_distance.y = 1e30;
	else
		ray->delta_distance.y = fabs(1 / ray->direction.y);
	get_ray_side_distance(ray, map);
}

int	get_texture_x_position(t_map *map, t_ray *ray, int *x, int *side)
{
	double	wall_x;
	int		result;

	if (*side == 0)
		wall_x = map->player->position->y
			+ map->player->walls_perp_distance[*x] * ray->direction.y;
	else
		wall_x = map->player->position->x
			+ map->player->walls_perp_distance[*x] * ray->direction.x;
	wall_x -= floor((wall_x));
	result = (int)(wall_x * TEXTURE_WIDTH);
	if ((*side == 0 && ray->direction.x > 0)
		|| (*side == 1 && ray->direction.y < 0))
		result = TEXTURE_WIDTH - result - 1;
	return (result);
}

int	get_texture_y_position(int *draw_start, int *line_height)
{
	double	step;
	double	texture_distance;

	step = 1.0 * TEXTURE_HEIGHT / *line_height;
	texture_distance
		= *draw_start - SCREEN_HEIGHT / 2 + *line_height / 2;
	return (texture_distance * step);
}

t_img	*get_texture(t_map *map, t_ray *ray, int *side)
{
	if (ray->hit == 2)
		return (map->door_texture);
	if (ray->direction.x >= 0 && ray->direction.y >= 0 && *side == 0)
		return (map->south_texture);
	else if (ray->direction.x >= 0 && ray->direction.y >= 0 && *side == 1)
		return (map->east_texture);
	else if (ray->direction.x < 0 && ray->direction.y >= 0 && *side == 0)
		return (map->north_texture);
	else if (ray->direction.x < 0 && ray->direction.y >= 0 && *side == 1)
		return (map->east_texture);
	else if (ray->direction.x < 0 && ray->direction.y < 0 && *side == 0)
		return (map->north_texture);
	else if (ray->direction.x < 0 && ray->direction.y < 0 && *side == 1)
		return (map->west_texture);
	else if (ray->direction.x >= 0 && ray->direction.y < 0 && *side == 0)
		return (map->south_texture);
	else
		return (map->west_texture);
}

void	draw_column(t_display *display, t_ray *ray, int *x, int *side)
{
	t_dot_index	texture_position;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;

	texture_position.x = get_texture_x_position(display->map, ray, x, side);
	line_height
		= (int)(SCREEN_HEIGHT / display->map->player->walls_perp_distance[*x]);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	texture_position.y = get_texture_y_position(&draw_start, &line_height);
	while (draw_start < draw_end)
	{
		texture_position.y = get_texture_y_position(&draw_start, &line_height);
		color = get_pixel_color(get_texture(display->map, ray, side),
				&texture_position);
		if ((color & 0x00FFFFFF) != 0)
			put_pixel_on_img(display->new_img, *x, draw_start, color);
		++draw_start;
	}
}
