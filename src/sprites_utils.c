/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:09:22 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/27 15:57:29 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_sprite	**get_sprites_array(t_display *display, t_sprite *sprites_lst)
{
	t_sprite	**result;
	t_sprite	*temp;
	int			i;

	result = malloc(sizeof(t_sprite *) * display->map->nbr_sprites);
	if (!result)
		strerror_and_exit(display, "malloc ordered sprites array");
	i = -1;
	temp = sprites_lst;
	while (temp)
	{
		result[++i] = temp;
		temp = temp->next;
	}
	return (result);
}

void	get_sprites_distance(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->nbr_sprites)
	{
		map->sprites_array[i]->dist = pow(map->player->position->x
				- map->sprites_array[i]->x, 2) + pow(map->player->position->y
				- map->sprites_array[i]->y, 2);
	}
}

void	swap_sprites(t_sprite **sprites_array, int i, int j)
{
	t_sprite	*temp;

	temp = sprites_array[i];
	sprites_array[i] = sprites_array[j];
	sprites_array[j] = temp;
}

int	sort_section(t_sprite **sprites_array, int first, int last)
{
	int			i;
	int			j;
	int			pivot;

	pivot = first;
	i = first;
	j = last;
	while (i < j)
	{
		while (sprites_array[i]->dist <= sprites_array[pivot]->dist && i < last)
			++i;
		while (sprites_array[j]->dist > sprites_array[pivot]->dist)
			--j;
		if (i < j)
			swap_sprites(sprites_array, i, j);
	}
	swap_sprites(sprites_array, pivot, j);
	return (j);
}

void	sort_sprites_array(t_sprite **sprites_array, int first, int last)
{
	int	i;

	if (first < last)
	{
		i = sort_section(sprites_array, first, last);
		sort_sprites_array(sprites_array, first, i - 1);
		sort_sprites_array(sprites_array, i + 1, last);
	}
}
