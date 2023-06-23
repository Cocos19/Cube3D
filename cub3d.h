/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:17:46 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/23 13:56:50 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

# define WIDTH 1280
# define HEIGHT 1024

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_img;

typedef struct s_map
{
	int	celling_color;
	int	floor_color;
}	t_map;

typedef struct s_display_datas
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	*old_img;
	t_img	*new_img;
}	t_display;

/*ERROR HANDLING*/

void	strerror_and_exit(t_display *display, char *error_msg);

/*MEMORY FREE*/

void	free_display(t_display *display);

/*IMAGE MANAGEMENT*/

void	encode_pixel_rgb(int *pixel, uint8_t red, uint8_t green, uint8_t blue);
void	render_background(t_img *image, t_display *display);
t_img	*init_image(t_display *display);

/*LOOPS ANF HOOKS*/

int		ft_mlx_hook(t_display *display);
int		ft_loop_hook(t_display *display);
int		ft_key_hook(int key, t_display *display);

#endif
