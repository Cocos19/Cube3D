/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:08:10 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/27 16:11:38 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_door_ray_side_distance(t_ray *ray, t_map *map)
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

void	init_door_ray(t_ray *ray, t_map *map)
{
	ray->direction.x = map->player->direction->x;
	ray->direction.y = map->player->direction->y;
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
	get_door_ray_side_distance(ray, map);
}

double	get_door_distance(t_dot *origin, t_dot_index *end_point)
{
	return (sqrtf(pow(end_point->x - origin->x, 2)
			+ pow(end_point->x - origin->x, 2)));
}

/*This function will cast a ray in player FOV direction and
check if it reach a door. If a door is right in front of the player
and in interaction reach, it will transform the door tile, in an empty tile*/

int	open_door(t_map *map)
{
	t_ray		ray;

	init_door_ray(&ray, map);
	while (1)
	{
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
		if (map->tiles[(int)ray.origin.x][(int)ray.origin.y] == 'D'
			&& get_door_distance(map->player->position, &ray.origin)
				<= INTERACT_REACH)
		{
			map->tiles[(int)ray.origin.x][(int)ray.origin.y] = '0';
			return (0);
		}
		else if (map->tiles[(int)ray.origin.x][(int)ray.origin.y] == '1')
			return (0);
	}
}
