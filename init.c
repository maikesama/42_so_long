/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:52:30 by mpaci             #+#    #+#             */
/*   Updated: 2021/11/08 14:52:32 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	struct_init(t_data *m)
{
	m->column = 0;
	m->line_cnt = 0;
	m->player = 0;
	m->pl_x = 0;
	m->pl_y = 0;
	m->cash = 0;
	m->exit = 0;
	m->tile = 0;
	m->moves = 0;
	m->kill = 0;
}

void	ft_init_img(t_data *v, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(v->mlx, path, &img->w, &img->h);
	img->addr = mlx_get_data_addr(
			img->img, &img->bpp, &img->line_length, &img->endian);
}

void	ft_mlx_init(t_data *v)
{
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, v->column * 32,
			v->line_cnt * 32, "SO_LONG");
	v->img = mlx_new_image(v->mlx, 32 * v->column,
			32 * v->line_cnt);
	v->addr = mlx_get_data_addr(v->img, &v->bpp,
			&v->line_length, &v->endian);
	ft_init_img(v, &v->exit_img, "./textures/exit.xpm");
	ft_init_img(v, &v->wall_img, "./textures/wall.xpm");
	ft_init_img(v, &v->player_img, "./textures/runfrog.xpm");
	ft_init_img(v, &v->cash_img, "./textures/coll.xpm");
	ft_init_img(v, &v->floor_img, "./textures/floor.xpm");
	ft_init_img(v, &v->enemy_img, "./textures/exot.xpm");
	ft_map_print(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
}

void	ft_destroy_img(t_data *v, t_img *img)
{
	mlx_destroy_image(v->mlx, img->img);
}

void	ft_mlx_destroy(t_data	*v)
{
	if (v->cash <= 0 && v->map[v->pl_y][v->pl_x] == 'E')
		ft_printf("YOU'VE COMPLETED THE GAME! SEE YOU NEXT TIME <3");
	else
		ft_printf("YOU'VE LOST AND KILLED THE FROG :(");
	clean_map(v);
	ft_destroy_img(v, &v->player_img);
	ft_destroy_img(v, &v->wall_img);
	ft_destroy_img(v, &v->cash_img);
	ft_destroy_img(v, &v->exit_img);
	ft_destroy_img(v, &v->floor_img);
	mlx_destroy_image(v->mlx, v->img);
	mlx_destroy_window(v->mlx, v->win);
	exit (0);
}
