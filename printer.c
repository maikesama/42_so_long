/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:52:51 by mpaci             #+#    #+#             */
/*   Updated: 2021/11/08 14:52:53 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (color < 0xff000000)
	{
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	ft_tex_pri(t_data *v, t_img *img, int frame_y, int frame_x)
{
	int		x;
	int		y;
	int		reset_x;
	int		line;
	char	*addr;

	addr = img->addr;
	line = 0;
	reset_x = frame_x;
	y = -1;
	while (++y < img->h)
	{
		x = -1;
		while (++x < img->w)
		{
			my_mlx_pixel_put(v, frame_x, frame_y, *(unsigned int *) addr);
			addr += img->bpp / 8;
			frame_x++;
		}
		frame_x = reset_x;
		frame_y++;
		addr = img->addr + img->line_length * ++line;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
}

void	ft_map_print(t_data *v)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (v->map[++y])
	{
		x = -1;
		while (v->map[y][++x])
		{
			ft_tex_pri(v, &v->floor_img, y * 32, x * 32);
			if (v->map[y][x] == '1')
				ft_tex_pri(v, &v->wall_img, y * 32, x * 32);
			if (v->map[y][x] == 'C')
				ft_tex_pri(v, &v->cash_img, y * 32, x * 32);
			if (v->map[y][x] == 'E')
				ft_tex_pri(v, &v->exit_img, y * 32, x * 32);
			if (v->map[y][x] == 'N')
				ft_tex_pri(v, &v->enemy_img, y * 32, x * 32);
		}
	}
}

void	print_playa(t_data *v, t_img *img, int frame_x, int frame_y)
{
	int		x;
	int		y;
	int		reset_x;
	int		line;
	char	*addr;

	addr = img->addr + (img->bpp / 8 * img->w / TILESET * v->tile);
	line = 0;
	reset_x = frame_x;
	y = -1;
	while (++y < img->h)
	{
		x = -1;
		while (++x < img->w / TILESET)
		{
			my_mlx_pixel_put(v, frame_x, frame_y, *(unsigned int *) addr);
			frame_x++;
			addr += img->bpp / 8;
		}
		frame_x = reset_x;
		frame_y++;
		addr = img->addr + (img->bpp / 8 * img->w / TILESET * v->tile)
			+ img->line_length * ++line;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
}

void	move_player(t_data *v, int y, int x)
{
	if (v->map[v->pl_y + y][v->pl_x + x] != '1')
	{
		v->moves++;
		v->prev_px = v->pl_x;
		v->prev_py = v->pl_y;
		v->pl_x += x;
		v->pl_y += y;
		if (v->map[v->pl_y][v->pl_x] == 'C')
		{
			ft_tex_pri(v, &v->floor_img, (v->pl_y) * 32,
				(v->pl_x) * 32);
			v->cash--;
		}
		if ((v->map[v->pl_y][v->pl_x] == 'E' && v->cash <= 0))
			ft_mlx_destroy(v);
		if (v->map[v->pl_y][v->pl_x] == 'N')
			ft_mlx_destroy(v);
		if (v->map[v->prev_py][v->prev_px] == 'E')
		{
			ft_tex_pri(v, &v->floor_img, v->prev_py * 32, v->prev_px * 32);
			ft_tex_pri(v, &v->exit_img, v->prev_py * 32, v->prev_px * 32);
		}
		else
			ft_tex_pri(v, &v->floor_img, v->prev_py * 32, v->prev_px * 32);
	}
}
