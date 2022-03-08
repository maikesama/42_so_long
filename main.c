/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:52:03 by mpaci             #+#    #+#             */
/*   Updated: 2021/11/08 14:52:07 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exec(t_data *v)
{
	static int	time;
	char		*moves;

	mlx_sync(1, v->player_img.img);
	ft_tex_pri(v, &v->floor_img, v->pl_y * 32, v->pl_x * 32);
	print_playa(v, &v->player_img, v->pl_x * 32, v->pl_y * 32);
	if (!(++time % 2))
		v->tile++;
	if (v->tile == TILESET)
		v->tile = 0;
	moves = ft_itoa(v->moves);
	if (!moves)
		ft_mlx_destroy(v);
	free (moves);
	mlx_string_put(v->mlx, v->win, 5, 18, 0x7A1712, moves);
	mlx_sync(3, v->win);
	if (v->kill == 1)
		ft_mlx_destroy(v);
	return (0);
}

static int	keypress(int code, t_data *all)
{
	if (code == ESC)
		all->kill = 1;
	if (code == KEY_W)
		move_player(all, -1, 0);
	if (code == KEY_A)
		move_player(all, 0, -1);
	if (code == KEY_S)
		move_player(all, 1, 0);
	if (code == KEY_D)
		move_player(all, 0, 1);
	return (1);
}

static int	kill(t_data *all)
{
	all->kill = 1;
	return (0);
}

void	event_hooks(t_data *all)
{
	mlx_hook(all->win, 2, 1L << 0, keypress, all);
	mlx_hook(all->win, 17, 1L << 17, kill, all);
}

int	main(int argc, char **argv)
{
	t_data	all;

	if (!args_check(argc, argv))
		return (0);
	valid_fd(argv, &all);
	struct_init(&all);
	if (!processing_map(&all))
		return (0);
	if (!wall_check(&all) || !element_check(&all))
	{
		ft_printf("Invalid map or elements.\n");
		clean_map(&all);
		return (0);
	}
	ft_mlx_init(&all);
	event_hooks(&all);
	mlx_loop_hook(all.mlx, exec, &all);
	mlx_loop(all.mlx);
	return (0);
}
