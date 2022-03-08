/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:58:51 by mpaci             #+#    #+#             */
/*   Updated: 2021/11/08 14:58:54 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "./lib/mlx/mlx.h"
# include "./lib/libft/libft.h"
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define ESC 53
# define TILESET 12

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		w;
	int		h;
	char	*path;
}			t_img;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	void	*win;
	void	*mlx;
	int		moves;
	int		move_x;
	int		move_y;
	int		prev_px;
	int		prev_py;

	t_img	wall_img;
	t_img	floor_img;
	t_img	player_img;
	t_img	cash_img;
	t_img	exit_img;
	t_img	enemy_img;

	char	**map;
	int		fd;
	int		line_cnt;
	int		column;
	char	*line;
	char	**tmp;
	int		i;
	int		y;
	int		x;
	int		s;
	int		l;
	int		ret;

	int		player;
	int		cash;
	int		exit;
	int		pl_x;
	int		pl_y;
	int		kill;

	int		tile;
}		t_data;

void	custom_mlx_pixel_put(t_data *data, int x, int y, int color);
int		processing_map(t_data *all);
int		wall_check(t_data *all);
int		element_check(t_data *all);
void	clean_map(t_data *all);
void	get_player_position(t_data *all);
int		key_hook(int keycode);
int		ft_gnl(int fd, char **line);
int		ft_printf(const char *str, ...);
void	struct_init(t_data *m);
void	ft_mlx_destroy(t_data	*v);
void	ft_mlx_init(t_data *v);
void	ft_map_print(t_data *v);
void	move_player(t_data *v, int y, int x);
void	print_playa(t_data *v, t_img *img, int frame_x, int frame_y);
void	ft_tex_pri(t_data *v, t_img *img, int frame_y, int frame_x);
void	ft_map_print(t_data *v);
void	valid_fd(char **argv, t_data *m);
void	get_player_position(t_data *all);
int		args_check(int argc, char **argv);
void	clean_map(t_data *m);
#endif
