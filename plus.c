/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:52:45 by mpaci             #+#    #+#             */
/*   Updated: 2021/11/08 14:52:47 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	valid_fd(char **argv, t_data *m)
{
	int	err;

	m->fd = open(argv[1], O_RDONLY);
	err = errno;
	if (m->fd == -1)
	{
		ft_printf("fd is not valid.\n");
		perror(strerror(err));
		exit(1);
	}
}

void	get_player_position(t_data *all)
{
	all->l = -1;
	while (++all->l < all->line_cnt)
	{
		all->x = -1;
		while (++all->x < all->column)
		{
			if (all->map[all->l][all->x] == 'P')
			{
				all->pl_x = all->x;
				all->pl_y = all->l;
			}
		}
	}
}

int	args_check(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Wrong number of arguments\n");
		return (0);
	}
	if (ft_memcmp((&argv[1][ft_strlen(argv[1]) - 4]), ".ber", 4))
	{
		ft_printf("Map need to be a .ber file\n");
		return (0);
	}
	return (1);
}

void	clean_map(t_data *m)
{
	int	i;

	i = -1;
	while (m->map[++i])
	{
		free (m->map[i]);
	}
	free (m->map);
}
