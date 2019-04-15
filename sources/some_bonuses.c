/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_bonuses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:15:25 by vkremen           #+#    #+#             */
/*   Updated: 2019/03/16 17:15:28 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		usage(void)
{
	ft_printf("usage: ./lem-in [input] [-c | -w]\n\n");
	ft_printf("\t\t\tINPUT:\n");
	ft_printf("\t\t\t->[Run without parameters to read stdin]\n");
	ft_printf("\t\t\t->[Input filename as a parameter to read from it]\n\n");
	ft_printf("\t\t\tFLAGS: (optional)\n");
	ft_printf("\t\t\t-c [Prints number of lines with ant movements]\n");
	ft_printf("\t\t\t-w [Prints paths which");
	ft_printf(" algorithm found from Start to End]\n");
	exit(1);
}
