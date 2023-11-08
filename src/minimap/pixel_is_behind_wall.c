/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_is_behind_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:48:24 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/07 16:15:55 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_next_coord	get_next_abscissa_intersec(t_next_coord *origin, double *angle)
{
	t_next_coord result;

	if (*angle >= 0 && *angle <= PI)
		result.y = floor(origin->y);
	else
		result.y = ceil(origin->y);
	if (*angle >= 0 && *angle <= PI / 2)
		result.x = ((origin->y - (origin->y / 1) * 1)) / tan(*angle);
	else if ((*angle > PI / 2 && *angle <= PI))
		result.x = ((origin->y - (origin->y / 1) * 1)) / tan(*angle - (PI / 2));
	else if ((*angle > PI && *angle <= (3 * PI) / 2))
		result.x = ((origin->y - (origin->y / 1) * 1)) / tan(*angle - (PI));
	else if ((*angle > (3 * PI) / 2) && *angle <= 2 * PI)
		result.x = ((origin->y - (origin->y / 1) * 1)) / tan(*angle - (3 * PI) / 2);
	result.next_intersection = 'y';
	printf("result.x in abscisse: %f\n", result.x);
	return (result);
}

t_next_coord	get_next_ordinate_intersec(t_next_coord *origin, double *angle)
{
	t_next_coord result;

	if ((*angle >= PI / 2 && *angle <= (3 * PI) / 2))
		result.x = floor(origin->x);
	else
		result.x = ceil(origin->x);
	if (*angle >= 0 && *angle <= PI / 2)
		result.y = (1 - (origin->x / 1) * 1) / tan(*angle);
	else if ((*angle > PI / 2 && *angle <= PI))
		result.y = (1 - (origin->x / 1) * 1) / tan(*angle - (PI / 2));
	else if ((*angle > PI && *angle <= (3 * PI) / 2))
		result.y = (1 - (origin->x / 1) * 1) / tan(*angle - (PI));
	else if ((*angle > (3 * PI) / 2) && *angle <= 2 * PI)
		result.y = (1 - (origin->x / 1) * 1) / tan(*angle - (3 * PI) / 2);
	result.next_intersection = 'x';
	printf("result.x in ordinate: %f\n", result.x);
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

int	pixel_is_behind_wall(t_map *map, t_coord *pixel, double *angle)
{
	t_next_coord next_intersec;
	t_coord		pix_relative_position_on_minimap;

	int	count;

	count = 0;

	next_intersec.x = map->player->x;
	next_intersec.y = map->player->y;
	next_intersec.next_intersection = 0;
	pix_relative_position_on_minimap.x = map->player->x - (pixel->x / MINIMAP_SCALE);
	pix_relative_position_on_minimap.y = map->player->y - (pixel->y / MINIMAP_SCALE);
	printf("pixel.x: %f pixel.y: %f next_intersec.x: %f next_intersec.y: %f\n", pix_relative_position_on_minimap.x, pix_relative_position_on_minimap.y, next_intersec.x, next_intersec.y);
	while(!(floor(next_intersec.y) == floor(pix_relative_position_on_minimap.y)
		&& floor(next_intersec.x) == floor(pix_relative_position_on_minimap.x)))
	{
		if ((int)floor(next_intersec.y) >= 7 || (int)floor(next_intersec.y) < 0 || (int)floor(next_intersec.x) < 0 || map->tiles[(int)floor(next_intersec.y)][(int)floor(next_intersec.x)] == 1)
			return (1);
		get_nearest_pixel_intersection(&next_intersec, angle);
		printf("pixel.x: %f pixel.y: %f next_intersec.x: %f next_intersec.y: %f\n", pix_relative_position_on_minimap.x, pix_relative_position_on_minimap.y, next_intersec.x, next_intersec.y);
		++count;
		if (count > 20 || (int)floor(next_intersec.y) > 7 || (int)floor(next_intersec.x) > 7)
			return (1);
	}
	return (1);
}
