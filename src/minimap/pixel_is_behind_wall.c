/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_is_behind_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:48:24 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/10 13:57:22 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	convert_y_to_index_or_coordinate_value(t_map *map, double *y)
{
	*y = map->map_height - *y;
}

t_next_coord	get_next_abscissa_intersec(t_next_coord *origin, double *angle)
{
	t_next_coord result;

	if (*angle >= 0 && *angle <= PI)
	{
		if (origin->y == ceil(origin->y))
			result.y = origin->y + 1;
		else
			result.y = ceil(origin->y);
	}
	else
	{
		if (origin->y == floor(origin->y))
			result.y = origin->y - 1;
		else
			result.y = floor(origin->y);
	}
	result.x = origin->x + (origin->y - floor(origin->y)) / tan(*angle);
	result.next_intersection = 'y';
	return (result);
}

t_next_coord	get_next_ordinate_intersec(t_next_coord *origin, double *angle)
{
	t_next_coord result;

	if ((*angle >= PI / 2 && *angle <= (3 * PI) / 2))
	{
		if (origin->x == floor(origin->x))
			result.x = origin->x - 1;
		else
			result.x = floor(origin->x);
	}
	else
	{
		if (origin->x == ceil(origin->x))
			result.x = origin->x + 1;
		else
			result.x = ceil(origin->x);
	}
	result.y = origin->y + ((origin->x - floor(origin->x)) * tan(*angle));
	result.next_intersection = 'x';
	return (result);
}

int	is_closer(t_next_coord *origin, t_next_coord *p1, t_next_coord *p2)
{
	if (sqrtf(pow(p1->x - origin->x, 2) + pow(p1->y - origin->y, 2))
		< sqrtf(pow(p2->x - origin->x, 2) + pow(p2->y - origin->y, 2)))
		return (0);
	return (1);
}

void	get_nearest_pixel_intersection(t_next_coord *origin, double *angle)
{
	t_next_coord	result;
	t_next_coord	temp;
	if (origin->next_intersection == 0)
	{
		result = get_next_abscissa_intersec(origin, angle);
		temp = get_next_ordinate_intersec(origin, angle);
		if (is_closer(origin, &result, &temp) == 1)
			result = temp;
	}
	else if (origin->next_intersection == 'x')
		result = get_next_abscissa_intersec(origin, angle);
	else if (origin->next_intersection == 'y')
		result = get_next_ordinate_intersec(origin, angle);
	origin->x = result.x;
	origin->y = result.y;
	origin->next_intersection = result.next_intersection;
}

// int	pixel_is_behind_wall(t_map *map, t_coord *pixel, double *angle)
// {
// 	t_coord			dot;
// 	t_next_coord	next;
// 	int				segfault_protection;

// 	dot.x = map->player->x - (pixel->x / MINIMAP_SCALE);
// 	dot.y = map->player->y - (pixel->y / MINIMAP_SCALE);
// 	next.next_intersection = 0;
// 	next.x = map->player->x;
// 	next.y = map->player->y;
// 	convert_y_to_index_or_coordinate_value(map, &next.y);
// 	convert_y_to_index_or_coordinate_value(map, &dot.y);
// 	segfault_protection = 0;
// 	while(!(floor(next.y) == floor(dot.y) && floor(next.x) == floor(dot.x)))
// 	{
// 		convert_y_to_index_or_coordinate_value(map, &next.y);
// 		if ((int)floor(next.y) >= 7 || (int)floor(next.y) < 0 || map->tiles[(int)floor(next.y)][(int)floor(next.x)] == 1)
// 			return (1);
// 		convert_y_to_index_or_coordinate_value(map, &next.y);
// 		get_nearest_pixel_intersection(&next, angle);
// 		++segfault_protection;
// 		convert_y_to_index_or_coordinate_value(map, &next.y);
// 		if (segfault_protection > 10 || (int)floor(next.y) > 7 || (int)floor(next.x) > 7)
// 			return (1);
// 		convert_y_to_index_or_coordinate_value(map, &next.y);
// 	}
// 	return (0);
// }

// int	pixel_is_behind_wall(t_map *map, int *x, t_coord *pixel)
// {
// 	double		cameraX;
// 	double		perpendicular_wall_distance;
// 	t_vector	ray_direction;
// 	t_vector	side_distance;
// 	t_vector	delta_distance;
// 	t_dot		map_location;
// 	int			stepX;
// 	int			stepY;
// 	int			hit;
// 	int			side;

// 	cameraX = 2 * *x / (double)(SCREEN_WIDTH) - 1;
// 	ray_direction.x = map->player->direction->x + map->player->plane->x * cameraX;
// 	ray_direction.y = map->player->direction->y + map->player->plane->y * cameraX;
// 	map_location.x = (int)map->player->position->x;
// 	map_location.y = (int)map->player->position->y;
// 	hit = 0;
// 	stepX = 0;
// 	stepY = 0;
// 	if (ray_direction.x == 0)
// 		delta_distance.x = LONG_MAX;
// 	else
// 		delta_distance.x = fabs(1 / ray_direction.x);
// 	if (ray_direction.y == 0)
// 		delta_distance.y = LONG_MAX;
// 	else
// 		delta_distance.y = fabs(1 / ray_direction.y);
// 	if (ray_direction.x < 0)
// 	{
// 		stepX = -1;
// 		side_distance.x = (map->player->position->x - map_location.x) * delta_distance.x;
// 	}
// 	else
// 	{
// 		stepX = 1;
// 		side_distance.x = (map_location.x + 1.0 - map->player->position->x) * delta_distance.x;
// 	}
// 	if (ray_direction.y < 0)
// 	{
// 		stepY = -1;
// 		side_distance.y = (map->player->position->y - map_location.y) * delta_distance.y;
// 	}
// 	else
// 	{
// 		stepY = 1;
// 		side_distance.y = (map_location.y + 1.0 - map->player->position->y) * delta_distance.y;
// 	}
// 	while(hit == 0)
// 	{
// 		if (side_distance.x < side_distance.y)
// 		{
// 			side_distance.x += delta_distance.x;
// 			map_location.x += stepX;
// 			side = 0;
// 		}
// 		else
// 		{
// 			side_distance.y += delta_distance.y;
// 			map_location.y += stepY;
// 			side = 1;
// 		}
// 		if (map->tiles[(int)map_location.x][(int)map_location.y] == '1')
// 			hit = 1;
// 	}
// }
