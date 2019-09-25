/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:53:32 by koparker          #+#    #+#             */
/*   Updated: 2019/09/23 16:55:59 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	balance_delta_for_color(t_point *p1, t_point *p2, t_gradient *gr)
{
	(*gr).delta = p2->x - p1->x;
	(*gr).flag = p2->y - p1->y;
	if ((*gr).delta > (*gr).flag)
		(*gr).flag = 0;
	else
	{
		(*gr).delta = (*gr).flag;
		(*gr).flag = 1;
	}
}
