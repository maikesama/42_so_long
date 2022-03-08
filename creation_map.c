/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:52:14 by mpaci             #+#    #+#             */
/*   Updated: 2021/11/08 14:52:17 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	element_check(t_data *m)
{
	if (m->line_cnt < 3 || m->column < 3 || m->line_cnt == m->column)
		return (0);
	m->x = -1;
	while (++m->x < m->line_cnt)
	{
		m->l = -1;
		while (++m->l < m->column)
		{
			if (m->map[m->x][m->l] == 'P')
				m->player += 1;
			if (m->map[m->x][m->l] == 'C')
				m->cash += 1;
			if (m->map[m->x][m->l] == 'E')
				m->exit += 1;
		}
	}
	if (m->player != 1 || m->exit != 1 || m->cash == 0)
		return (0);
	get_player_position(m);
	return (1);
}

int	map_content_check(t_data *m)
{
	int		err;
	char	*str;

	str = "10PCEN";
	m->x = -1;
	while (++m->x < m->line_cnt)
	{
		m->s = -1;
		while (++m->s < m->column)
		{
			m->l = -1;
			err = 1;
			while (str[++m->l])
			{
				if (m->map[m->x][m->s] == str[m->l])
					err = 0;
			}
			if (err == 1)
				return (0);
		}
	}
	return (1);
}

int	wall_check(t_data *m)
{
	int	i;

	i = -1;
	while (m->map[0][++i])
	{
		if (m->map[0][i] != '1' || m->map[m->line_cnt - 1][i] != '1')
			return (0);
		m->column++;
	}
	i = 0;
	while (++i < m->line_cnt - 1)
	{
		if (m->map[i][0] != '1' || m->map[i][m->column - 1] != '1')
			return (0);
	}
	i = -1;
	while (++i < m->line_cnt)
	{
		if (ft_strlen(m->map[i]) != m->column)
			return (0);
	}
	if (!map_content_check(m))
		return (0);
	return (1);
}

char	*read_all(int fd)
{
	char	*buff;
	char	*str;
	size_t	ret;

	ret = 1;
	str = ft_calloc(1, 1);
	buff = ft_calloc(41, 1);
	while (ret > 0)
	{
		ret = read(fd, buff, 40);
		str = ft_strjoin(str, buff);
		ft_memset(buff, 0, 41);
	}
	return (str);
}

int	processing_map(t_data *m)
{
	char	*str;
	int		i;

	str = read_all(m->fd);
	i = -1;
	m->map = ft_split(str, '\n');
	while (m->map[++i])
		++m->line_cnt;
	return (1);
}
