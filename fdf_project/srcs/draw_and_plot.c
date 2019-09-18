/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_and_plot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:19:15 by koparker          #+#    #+#             */
/*   Updated: 2019/09/18 17:51:24 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void	draw_line_low(t_point *p1, t_point *p2, int **img_arr, t_data *data)
{
	t_draw_line	l;

	l.dx = p2->x - p1->x;
	l.dy = p2->y - p1->y;
	l.y_i = 1;
	if (l.dy < 0)
	{
		l.y_i = -l.y_i;
		l.dy = -l.dy;
	}
	l.diff = 2 * l.dy - l.dx;
	l.y = p1->y + SHIFT_Y / 2;
	l.x = p1->x + SHIFT_X / 2;
	while (l.x < p2->x + SHIFT_X / 2)
	{
		if (l.x >= 0 && l.y >= 0 && l.y < DH_IM * DW_IM && l.x < DW_IM)
			(*img_arr)[l.y * DW_IM + l.x] = 0xFFFFFF;
		if (l.diff > 0)
		{
			l.y = l.y + l.y_i;
			l.diff = l.diff - 2 * l.dx;
		}
		l.diff = l.diff + 2 * l.dy;
		l.x++;
	}
}

static void	draw_line_high(t_point *p1, t_point *p2, int **img_arr,
						t_data *data)
{
	t_draw_line	l;

	l.dx = p2->x - p1->x;
	l.dy = p2->y - p1->y;
	l.x_i = 1;
	if (l.dx < 0)
	{
		l.x_i = -l.x_i;
		l.dx = -l.dx;
	}
	l.diff = 2 * l.dx - l.dy;
	l.y = p1->y + SHIFT_Y / 2;
	l.x = p1->x + SHIFT_X / 2;
	while (l.y < p2->y + SHIFT_Y / 2 + 1)
	{
		if (l.x >= 0 && l.y >= 0 && l.y < DH_IM * DW_IM && l.x < DW_IM)
			(*img_arr)[l.x + l.y * DW_IM] = WHITE;
		if (l.diff > 0)
		{
			l.x = l.x + l.x_i;
			l.diff = l.diff - 2 * l.dy;
		}
		l.diff = l.diff + 2 * l.dx;
		l.y++;
	}
}

static void	plot(t_point *p1, t_point *p2, int **img_arr, t_data *data)
{
	if (abs(p2->y - p1->y) < abs(p2->x - p1->x))
	{
		if (p1->x > p2->x)
			draw_line_low(p2, p1, img_arr, data);
		else
			draw_line_low(p1, p2, img_arr, data);
	}
	else
	{
		if (p1->y > p2->y)
			draw_line_high(p2, p1, img_arr, data);
		else
			draw_line_high(p1, p2, img_arr, data);
	}
}

// TODO: add balancer-rotate/iso-by-button-click
void		draw_plane(t_point ***head, t_data *data, int **img_arr)
{
	size_t	i;
	size_t	j;

	apply_rotation(head, data, 7);
	apply_projection(head, data, 34);
	j = 0;
	while (j < data->size_y)
	{
		i = 0;
		while (i < data->size_x)
		{
			if (i < data->size_x - 1)
			{
				plot(&((*head)[j][i]), &((*head)[j][i + 1]), img_arr, data);
			}
			if (j < data->size_y - 1)
			{
				plot(&((*head)[j][i]), &((*head)[j + 1][i]), img_arr, data);
			}
			i++;
		}
		j++;
	}
}
