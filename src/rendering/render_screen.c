/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:48:37 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/06 20:40:45 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	render_background(t_img *image, t_display *display);
static void	cast_ray(t_display *display, t_ray *ray, int *side);
static void	update_walls_perp_dist(t_map *map, t_ray *ray, int *x, int *side);

void	render_image(t_img *image, t_display *display)
{
	t_ray	ray;
	int		x;
	int		side;

	render_background(image, display);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		side = 0;
		init_ray(&ray, display->map, &x);
		cast_ray(display, &ray, &side);
		update_walls_perp_dist(display->map, &ray, &x, &side);
		draw_column(display, &ray, &x, &side);
	}
}

static void	render_background(t_img *image, t_display *display)
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

/*
	Digital Differential Analysis algorithm used to increment the ray of
	1 map's square at a time either in the abscissa's or in th ordinate's
	direction according to the ray's slope.
*/
static void	cast_ray(t_display *display, t_ray *ray, int *side)
{
	while (ray->hit == 0)
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
		if (display->map->tiles[ray->origin.x][ray->origin.y] == '1')
			ray->hit = 1;
	}
}

/*
	Corrects the perspective to avoid the fish-eye effect
*/
static void	update_walls_perp_dist(t_map *map, t_ray *ray, int *x, int *side)
{
	if (*side == 0)
		map->player->walls_perp_distance[*x]
			= (ray->side_distance.x - ray->delta_distance.x);
	else
		map->player->walls_perp_distance[*x]
			= (ray->side_distance.y - ray->delta_distance.y);
}

/*
	Initializes the ray's slope according to the player's
	position and direction (indicated by step).
*/
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
