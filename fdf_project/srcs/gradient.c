/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:56:34 by koparker          #+#    #+#             */
/*   Updated: 2019/09/20 22:15:49 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static double	percent(int start, int end, int current, int flag)
{
	double placement;
	double distance;

	(flag == 1) ? (placement = current - start - SHIFT_Y)
				: (placement = current - start - SHIFT_X);
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

static int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

/*
** percent (start, end, current, flag)
** where flag == 0 for low and 1 for high
*/

int				get_color(t_point *p1, t_point *p2, int current)
{
	int		red;
	int		green;
	int		blue;
	int		delta_x;
	int		delta_y;
	double	percentage;

	// printf("color_1 = %d, color_2 = %d\n", p1->color, p2->color);
	delta_x = p2->x - p1->x;
	delta_y = p2->y - p1->y;
	if (p1->color == p2->color)
		return (p1->color);
	if (delta_x > delta_y)
		percentage = percent(p1->x, p2->x, current, 0);
	else
		percentage = percent(p1->y, p2->y, current, 1);
	red = get_light((p1->color >> 16) & 0xFF, (p2->color >> 16) & 0xFF, percentage);
	green = get_light((p1->color >> 8) & 0xFF, (p2->color >> 8) & 0xFF, percentage);
	blue = get_light((p1->color) & 0xFF, (p2->color) & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
