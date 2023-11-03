/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:13:26 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/03 17:04:37 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// double	get_scalar_product(t_coord *vector1, t_coord *vector2)
// {
// 	return ((vector1->x * vector2->x) + (vector1->y * vector2->y));
// }

// double	get_norm_vector(t_coord	*vector)
// {
// 	return (sqrtf((powf(vector->x, 2)) + powf(vector->y, 2)));
// }

// double	get_angle_between_3_dot_in_radian(t_coord *a, t_coord *b, t_coord *c)
// {
// 	t_coord	vector_ab;
// 	t_coord	vector_ac;
// 	double	result;

// 	vector_ab.x = b->x - a->x;
// 	vector_ab.y = b->y - a->y;
// 	vector_ac.x = c->x - a->x;
// 	vector_ac.y = c->y - a->y;
// 	result = acos(get_scalar_product(&vector_ab, &vector_ac)
// 			/ (get_norm_vector(&vector_ab) * get_norm_vector(&vector_ac)));
// 	if (b->y >= 0)
// 		return (result);
// 	else
// 		return (result + PI);
// }

int	radian_is_in_fov_range(t_map *map, double *radian)
{
	double	angle;
	double	min_angle;
	double	max_angle;

	angle = *radian * (180/PI);
	min_angle = map->player->view_angle - 45;
	if (min_angle < 0)
		min_angle += 360;
	max_angle = map->player->view_angle + 45;
	if (max_angle > 360)
		max_angle += 360;
	if (angle < max_angle && angle > min_angle)
		return (0);
	return (1);
}

double	get_angle_between_player_and_pixel(t_coord *pixel)
{
	double	result;

	result = acos((pixel->x * 5)
			/ (sqrtf((powf(pixel->x, 2)) + powf(pixel->y, 2)) * 5));
	if (pixel->y >= 0)
		return (result);
	else
		return (result + PI);
}

int	pixel_is_in_fov(t_map *map, t_coord *pixel)
{
	double	angle;

	angle = get_angle_between_player_and_pixel(pixel);
	if (radian_is_in_fov_range(map, &angle) == 0)
	{
		// if (pixel_is_behind_wall(map, *pixel, &angle))
		// 	return (1);
		// else
			return (0);
	}
	return (1);
}
