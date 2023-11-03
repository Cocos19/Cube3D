/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_is_behind_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:48:24 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/03 17:03:27 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
	t_coord	check_horizontal_intersection
	if (angle >= 0 && angle <= 180)
		result.y = floor(player.y)
	else
		result.y = ceil(player.y)
	if ((angle >= 270 && angle <= 360) || (angle >= 0 && angle <= 90))
	result.x = result.y / tan(angle)
*/

/*
	t_coord	check_vertical_intersection
	if ((angle >= 270 && angle <= 360) || (angle >= 0 && angle <= 90))
		result.x = ceil(player.x)
	else
		result.x = floor(player.x)
	result.y = result.x * tan(angle)
*/

/*
double	get_len_between_2_points
	return (sqrtf(pow(b.x - a.x) + pow(b.y - a.y)))
*/

/*
void	get_nearest_pixel_intersection
	check_horizontal_intersection;
	check_vertical_intersection;
	compare_hypothenuses;
	update_intersec_pixel(x, y, next_intersect);
*/

/*
void	get_next_pixel_intersection
	if (inter_pixel.next is VERTICAL)
		;
	else
		;
*/

/*
pixel_is_behind_wall
intersec_pixel = get_nearest_pixel_intersection;
while(1)
	pixel = get_next_pixel_intersection;
	is_next_intersection_index_an_empty_space;
		no = return (1);
	is_next_intersection_index_equal_to_pixel_index;
		yes = return (0);
*/

// int	pixel_is_behind_wall(t_map *map, t_coord pixel, double *angle)
// {

// }
