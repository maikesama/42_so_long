/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srcchar_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:17:45 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/26 15:17:48 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_srcchar_bonus(char *str, char c)
{
	while (str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}
