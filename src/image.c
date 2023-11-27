/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:48:37 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/27 16:10:09 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_minimap(t_img *image, t_display *display)
{
	int		x;
	int		y;
	t_dot	pixel;

	x = MINIMAP_CENTER_X - MINIMAP_DIAMETER / 2;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < MINIMAP_DIAMETER)
		{
			if (pixel_is_in_minimap_border(x, y) == 0)
				put_pixel_on_img(image, x, y,
					display->map->minimap_border_color);
			else if (pixel_is_in_minimap(x, y) == 0)
			{
				pixel.x = x;
				pixel.y = y;
				put_pixel_on_minimap(image, display->map, &pixel);
			}
		}
	}
}

void	render_background(t_img *image, t_display *display)
{
	int	x;
	int	y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			if (y < SCREEN_HEIGHT / 2)
				put_pixel_on_img(image, x, y, display->map->celling_color);
			else
				put_pixel_on_img(image, x, y, display->map->floor_color);
		}
	}
}

int	cast_ray(t_map *map, t_ray *ray, int *side)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_distance.x < ray->side_distance.y)
		{
			ray->side_distance.x += ray->delta_distance.x;
			ray->origin.x += ray->step_x;
			*side = 0;
		}
		else
		{
			ray->side_distance.y += ray->delta_distance.y;
			ray->origin.y += ray->step_y;
			*side = 1;
		}
		if (map->tiles[(int)ray->origin.x][(int)ray->origin.y] == '1')
			hit = 1;
		else if (map->tiles[(int)ray->origin.x][(int)ray->origin.y] == 'D')
			hit = 2;
	}
	return (hit);
}

void	raycast(t_display *display, int *x)
{
	t_ray	ray;
	int		hit;
	int		side;

	side = 0;
	init_ray(&ray, display->map, x);
	hit = cast_ray(display->map, &ray, &side);
	update_walls_perp_distance(display->map, &ray, x, &side);
	draw_column(display, &ray, x, &side);
}

void	render_image(t_img *image, t_display *display)
{
	int	x;

	render_background(image, display);
	x = -1;
	while (++x < SCREEN_WIDTH)
		raycast(display, &x);
	render_sprites(display->map, image, display->map->sprite_texture);
	render_minimap(image, display);
}
