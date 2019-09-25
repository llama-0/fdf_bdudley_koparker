/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:43:46 by koparker          #+#    #+#             */
/*   Updated: 2019/09/25 20:18:44 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int			get_max_z(t_data *data)
{
	size_t	i;
	size_t	j;
	int		max;

	j = 0;
	max = (data->arr)[0][0].alt;
	while (j < data->size_y)
	{
		i = 0;
		while (i < data->size_x)
		{
			if (max < (data->arr)[j][i].alt)
				max = (data->arr)[j][i].alt;
			i++;
		}
		j++;
	}
	return (max);
}

static void	iso(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x + previous_y) * (COS(30));
	*y = z + (previous_x - previous_y) * (-SIN(30));
}

static void	perspective(int *x, int *y, int z, double camera)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = trunc(previous_x * (1 - z / camera));
	*y = trunc(previous_y * (1 - z / camera));
}

void		apply_projection(t_data *data)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < data->size_y)
	{
		i = 0;
		while (i < data->size_x)
		{
			if (data->projection == ISO)
				iso(&(data->arr)[j][i].x, &(data->arr)[j][i].y,
						(data->arr)[j][i].z);
			else if (data->projection == CONIC)
				perspective(&(data->arr)[j][i].x, &(data->arr)[j][i].y,
						(data->arr)[j][i].z, data->camera);
			(data->arr)[j][i].x *= 1 + data->scale;
			(data->arr)[j][i].y *= 1 + data->scale;
			(data->arr)[j][i].z *= 1 + data->scale;
			i++;
		}
		j++;
	}
}
