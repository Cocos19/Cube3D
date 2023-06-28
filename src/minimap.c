/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:31:03 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/28 15:31:54 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	square(float nbr)
{
	return (nbr * nbr);
}

int	pixel_is_in_minimap(double x, double y)
{
	double	distance;
	double	radius;

	radius = 125;
	distance
		= sqrtf(square(x - (SCREEN_WIDTH - 125)) + square(y - 125)) - radius;
	if (distance <= -3.00000000)
		return (0);
	return (1);
}

int	pixel_is_in_minimap_border(double x, double y)
{
	double	distance;
	double	radius;

	radius = 125;
	distance
		= sqrtf(square(x - (SCREEN_WIDTH - 125)) + square(y - 125)) - radius;
	if (distance <= 0.00000000 && !(distance <= -3.00000000))
		return (0);
	return (1);
}
