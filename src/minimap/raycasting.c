/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:48:24 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/27 15:52:09 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	get_ray_side_distance(t_ray *ray, t_map *map)
{
	if (ray->direction.x < 0)
	{
		ray->step_x *= -1;
		ray->side_distance.x = (map->player->position->x - ray->origin.x)
			* ray->delta_distance.x;
	}
	else
		ray->side_distance.x = (ray->origin.x + 1.0 - map->player->position->x)
			* ray->delta_distance.x;
	if (ray->direction.y < 0)
	{
		ray->step_y *= -1;
		ray->side_distance.y = (map->player->position->y - ray->origin.y)
			* ray->delta_distance.y;
	}
	else
		ray->side_distance.y = (ray->origin.y + 1.0 - map->player->position->y)
			* ray->delta_distance.y;
}

void	init_minimap_ray(t_ray *ray, t_map *map, t_dot *end_point)
{
	ray->direction.x = end_point->x - map->player->position->x;
	ray->direction.y = end_point->y - map->player->position->y;
	ray->origin.x = map->player->position->x;
	ray->origin.y = map->player->position->y;
	ray->step_x = 1;
	ray->step_y = 1;
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

int	minimap_raycast(t_map *map, t_dot	*end_point)
{
	t_ray		ray;

	init_minimap_ray(&ray, map, end_point);
	while (1)
	{
		if ((int)ray.origin.x == (int)end_point->x
			&& (int)ray.origin.y == (int)end_point->y)
			return (0);
		if (ray.side_distance.x < ray.side_distance.y)
		{
			ray.origin.x += ray.step_x;
			ray.side_distance.x += ray.delta_distance.x;
		}
		else
		{
			ray.origin.y += ray.step_y;
			ray.side_distance.y += ray.delta_distance.y;
		}
		if (map->tiles[(int)ray.origin.x][(int)ray.origin.y] != '0')
			return (1);
	}
}
