/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:13:26 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/08 13:46:57 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	radian_is_in_fov_range(double *view_angle, double *angle)
{
	if (*view_angle < PI / 4)
	{
		if (*angle < *view_angle + (FOV / 2)
			|| *angle > (2 * PI) - (FOV / 2) + *view_angle)
			return (0);
	}
	else if (*view_angle > (7 * PI) / 4)
	{
		if (*angle < (FOV / 2) - (2 * PI) + *view_angle
			|| *angle > *view_angle - (FOV / 2))
			return (0);
	}
	else
	{
		if (*angle < *view_angle + (FOV / 2) && *angle > *view_angle - (FOV / 2))
			return (0);
	}
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
		return (PI + (PI - result));
}

int	pixel_is_in_fov(t_map *map, t_coord *pixel)
{
	double	angle;

	angle = get_angle_between_player_and_pixel(pixel);
	if (radian_is_in_fov_range(&map->player->view_angle, &angle) == 0)
	{
		// if (pixel_is_behind_wall(map, pixel, &angle))
		// 	return (1);
		// else
			return (0);
	}
	return (1);
}
