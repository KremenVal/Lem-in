/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 22:34:06 by vkremen           #+#    #+#             */
/*   Updated: 2018/11/01 14:10:14 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char const *s)
{
	int step;

	if (s != NULL)
	{
		step = 0;
		while (s[step])
		{
			write(1, &s[step], 1);
			step++;
		}
	}
	write(1, "\n", 1);
}
