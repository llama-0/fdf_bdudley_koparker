/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:56:34 by koparker          #+#    #+#             */
/*   Updated: 2019/09/23 16:54:32 by koparker         ###   ########.fr       */
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

static void		fn1(t_point *p, int mid, int current, t_gradient *gr)
{
	double		percentage;
	int			coord;

	coord = p->x;
	((*gr).flag == 0) ? (coord) : (coord = p->y);
	percentage = percent(coord, mid, current, (*gr).flag);
	(*gr).red = get_light((p->color >> 16) & 0xFF, (COLOR_MID >> 16)
							& 0xFF, percentage);
	(*gr).green = get_light((p->color >> 8) & 0xFF, (COLOR_MID >> 8)
							& 0xFF, percentage);
	(*gr).blue = get_light((p->color) & 0xFF, (COLOR_MID)
							& 0xFF, percentage);
}

static void		fn2(int mid, t_point *p, int current, t_gradient *gr)
{
	double		percentage;
	int			coord;

	coord = p->x;
	((*gr).flag == 0) ? (coord) : (coord = p->y);
	percentage = percent(mid, coord, current, (*gr).flag);
	(*gr).red = get_light((COLOR_MID >> 16) & 0xFF, (p->color >> 16)
											& 0xFF, percentage);
	(*gr).green = get_light((COLOR_MID >> 8) & 0xFF, (p->color >> 8)
											& 0xFF, percentage);
	(*gr).blue = get_light((COLOR_MID) & 0xFF, (p->color)
											& 0xFF, percentage);
}

/*
** percent (start, end, current, flag)
** where flag == 0 for low and 1 for high
*/

int				get_color(t_point *p1, t_point *p2, int current)
{
	t_gradient	gr;
	int			middle;

	if (p1->color == p2->color)
		return (p1->color);
	balance_delta_for_color(p1, p2, &gr);
	if (gr.flag == 0)
	{
		if (current < ((middle = gr.delta / 2 + p1->x) + SHIFT_X))
			fn1(p1, middle, current, &gr);
		else
			fn2(middle, p2, current, &gr);
	}
	else
	{
		if (current < ((middle = gr.delta / 2 + p1->y) + SHIFT_Y))
			fn1(p1, middle, current, &gr);
		else
			fn2(middle, p2, current, &gr);
	}
	return ((gr.red << 16) | (gr.green << 8) | gr.blue);
}
